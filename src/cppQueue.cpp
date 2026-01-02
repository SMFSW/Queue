/*!\file cppQueue.cpp
** \author SMFSW
** \copyright BSD 3-Clause License (c) 2017-2026, SMFSW
** \brief cppQueue handling library (designed on Arduino)
** \details cppQueue handling library (designed on Arduino)
**			This library was designed for Arduino, yet may be compiled without change with gcc for other purposes/targets
**/
/****************************************************************/
#include <cstring>
#include <cstdlib>

#include "cppQueue.h"
/****************************************************************/


#define QUEUE_INITIALIZED	0x5AA5U		//!< Initialized cppQueue control value


/**************************/
/*** INTERNAL FUNCTIONS ***/
/**************************/
/*!	\brief Increment index
**	\details Increment buffer index \b pIdx rolling back to \b start when limit \b end is reached
**	\param [in,out] pIdx - pointer to index value
**	\param [in] end - counter upper limit value
**	\param [in] start - counter lower limit value
**/
static inline void __attribute__((nonnull)) cppq_inc_idx(uint16_t * const pIdx, const uint16_t end, const uint16_t start)
{
	if (*pIdx < (end - 1U))
	{
		(*pIdx)++;
	}
	else
	{
		*pIdx = start;
	}
}

/*!	\brief Decrement index
**	\details Decrement buffer index \b pIdx rolling back to \b end when limit \b start is reached
**	\param [in,out] pIdx - pointer to index value
**	\param [in] end - counter upper limit value
**	\param [in] start - counter lower limit value
**/
static inline void __attribute__((nonnull)) cppq_dec_idx(uint16_t * const pIdx, const uint16_t end, const uint16_t start)
{
	if (*pIdx > start)
	{
		(*pIdx)--;
	}
	else
	{
		*pIdx = end - 1U;
	}
}


/*!	\brief get initialization state of the queue
**	\return cppQueue initialization status
**	\retval true if queue is allocated
**	\retval false is queue is not allocated
**/
inline bool __attribute__((always_inline)) cppQueue::_isInitialized(void) const {
	return (init == QUEUE_INITIALIZED); }

/*!	\brief get emptiness state of the queue
**	\return cppQueue emptiness status
**	\retval true if queue is empty
**	\retval false is not empty
**/
inline bool __attribute__((always_inline)) cppQueue::_isEmpty(void) const {
	return (cnt == 0U); }

/*!	\brief get fullness state of the queue
**	\return cppQueue fullness status
**	\retval true if queue is full
**	\retval false is not full
**/
inline bool __attribute__((always_inline)) cppQueue::_isFull(void) const {
	return (cnt == rec_nb); }


/*!	\brief get number of records in the queue
**	\return Number of records stored in the queue
**/
inline uint16_t __attribute__((always_inline)) cppQueue::_getCount(void) const {
	return cnt; }


/************************/
/*** PUBLIC FUNCTIONS ***/
/************************/
cppQueue::cppQueue(const size_t size_rec, const uint16_t nb_recs, const cppQueueType type, const bool overwrite, void * const pQDat, const size_t lenQDat)
{
	flush();					// variables needs to be 0 to ensure proper functions behavior when queue is not allocated
	init = 0;
	rec_nb = 0;					// rec_nb needs to be 0 to ensure proper push behavior when queue is not allocated
	ovw = false;				// ovw needs to be false to ensure proper push behavior when queue is not allocated
	dynamic = (pQDat == NULL);

	const size_t size = nb_recs * size_rec;

	if (dynamic)
	{
		queue = static_cast<uint8_t *>(malloc(size));
	}
	else if (lenQDat >= size)
	{
		queue = static_cast<uint8_t *>(pQDat);
	}
	else
	{
		queue = NULL;
	}

	if (queue != NULL)
	{
		queue_sz = size;
		rec_sz = size_rec;
		rec_nb = nb_recs;
		impl = type;
		ovw = overwrite;

		init = QUEUE_INITIALIZED;
	}
}

cppQueue::~cppQueue()
{
	if (_isInitialized() && dynamic && (queue != NULL))
	{
		free(queue);
	}
}


void cppQueue::flush(void)
{
	in = 0;
	out = 0;
	cnt = 0;
}


bool __attribute__((nonnull)) cppQueue::push(const void * const record)
{
	bool ret = true;

	if (_isFull())		// No more records available
	{
		if (ovw)		// cppQueue is full, overwrite is allowed
		{
			if (impl == FIFO)
			{
				cppq_inc_idx(&out, rec_nb, 0);	// as oldest record is overwritten, increment out
			}
			//else if (impl == LIFO)	{}	// Nothing to do in this case
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		cnt++;	// Increase records count
	}

	if (ret)
	{
		uint8_t * const pStart = queue + (rec_sz * in);
		(void) memcpy(pStart, record, rec_sz);
		cppq_inc_idx(&in, rec_nb, 0);
	}

	return ret;
}

bool __attribute__((nonnull)) cppQueue::pop(void * const record)
{
	bool ret = true;

	if (_isEmpty())	// No records
	{
		ret = false;
	}
	else
	{
		const uint8_t * pStart;

		if (impl == FIFO)
		{
			pStart = queue + (rec_sz * out);
			cppq_inc_idx(&out, rec_nb, 0);
		}
		else /* if (impl == LIFO) */
		{
			cppq_dec_idx(&in, rec_nb, 0);
			pStart = queue + (rec_sz * in);
		}

		(void) memcpy(record, pStart, rec_sz);
		cnt--;	// Decrease records count
	}

	return ret;
}


bool __attribute__((nonnull)) cppQueue::peek(void * const record)
{
	bool ret = true;

	if (_isEmpty())	// No records
	{
		ret = false;
	}
	else
	{
		const uint8_t * pStart;

		if (impl == FIFO)
		{
			pStart = queue + (rec_sz * out);
			// No change on out var as it's just a peek
		}
		else /*if (impl == LIFO)*/
		{
			uint16_t rec = in;	// Temporary var for peek (no change on in with dec_idx)
			cppq_dec_idx(&rec, rec_nb, 0);
			pStart = queue + (rec_sz * rec);
		}

		(void) memcpy(record, pStart, rec_sz);
	}

	return ret;
}


bool cppQueue::drop(void)
{
	bool ret = true;

	if (_isEmpty())	// No records
	{
		ret = false;
	}
	else
	{
		if (impl == FIFO)
		{
			cppq_inc_idx(&out, rec_nb, 0);
		}
		else /*if (impl == LIFO)*/
		{
			cppq_dec_idx(&in, rec_nb, 0);
		}

		cnt--;	// Decrease records count
	}

	return ret;
}


bool __attribute__((nonnull)) cppQueue::peekIdx(void * const record, const uint16_t idx)
{
	bool ret = true;

	if ((idx + 1U) > _getCount())	// Index out of range
	{
		ret = false;
	}
	else
	{
		const uint8_t * pStart;

		if (impl == FIFO)
		{
			pStart = queue + (rec_sz * ((out + idx) % rec_nb));
		}
		else /*if (impl == LIFO)*/
		{
			pStart = queue + (rec_sz * idx);
		}

		(void) memcpy(record, pStart, rec_sz);
	}

	return ret;
}


bool __attribute__((nonnull)) cppQueue::peekPrevious(void * const record)
{
	const uint16_t idx = _getCount() - 1U;	// No worry about count - 1 when queue is empty, test is done by peekIdx
	return peekIdx(record, idx);
}


/**********************/
/*** PUBLIC GETTERS ***/
/**********************/
bool cppQueue::isInitialized(void) const {
	return _isInitialized(); }

bool cppQueue::isEmpty(void) const {
	return _isEmpty(); }

bool cppQueue::isFull(void) const {
	return _isFull(); }

uint32_t cppQueue::sizeOf(void) const {
	return queue_sz; }

uint16_t cppQueue::getCount(void) const {
	return _getCount(); }

uint16_t cppQueue::getRemainingCount(void) const {
	return rec_nb - cnt; }

