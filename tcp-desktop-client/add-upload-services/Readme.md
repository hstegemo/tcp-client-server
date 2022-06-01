Service for adding SSH, Rsync, Google Drive or FTP settings to a service on the reMarkable.
This client is being developed for Windows 10.

Deploy Qt Application for Windows (Qt MinGW command shell): windeployqt.exe --qmldir project-folder  buildfolder\program.exe
 (https://evileg.com/en/post/163/):

If the project using QML
UPD 19.11.2018 by alex_lip :
If the project uses QML, then you need to add a special directive --qmldir
This directive will have to specify where to get the source of QML.
    windeployqt --qmldir f:\myApp\sources f:\build-myApp\myApp.exe

