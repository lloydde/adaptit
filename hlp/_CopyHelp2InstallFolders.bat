@echo off
Break ON
echo This batch file copies the HTML Help files to each of
echo the following installation folders for Setup Generator:
echo      1. Setup Regular
echo      2. Setup Regular Documentation Only
echo      3. Setup Unicode
echo      4. Setup Unicode Documentation Only
echo ===================================================
echo Adapt_It_Help.chm is copied to the setup Regular folder
echo Adapt_It_Help.chm is copied to the setup Regular Documentation Only folder
echo Adapt_It_Help.chm is copied to the setup Unicode folder
echo Adapt_It_Help.chm is copied to the setup Unicode Documentation Only folder
echo ===================================================
echo Press CRTL-C to abort or
pause

@echo on
rem The following copies the HTML Help file to the Setup Generator folders
@echo off
xcopy Adapt_It_Help.chm "..\setup Regular\" /Y
xcopy Adapt_It_Help.chm "..\setup Regular Documentation Only\" /Y
xcopy Adapt_It_Help.chm "..\setup Unicode\" /Y
xcopy Adapt_It_Help.chm "..\setup Unicode Documentation Only\" /Y
echo ===================================================
echo Copy process completed.
pause