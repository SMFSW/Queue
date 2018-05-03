@ECHO off
ECHO #***************************************************************
ECHO #	File : clean.bat
ECHO #
ECHO #	Command lines script:	Clearing output, temporary and log files
ECHO #***************************************************************


@ECHO on

::del *.o /s
del Queue.chm
del Queue.chw
del /f /q /s workdir\
rmdir workdir