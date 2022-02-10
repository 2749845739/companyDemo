import QtQuick 2.15
import QtQuick.Controls 2.5
import Qt.labs.platform 1.1

FolderDialog {
    id: floderDialog
    title: "Please choose a file"
//    folder:  StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
    signal floderPath(var path);
    onAccepted: {
        console.log("You chose: " + floderDialog.currentFolder)
        floderPath(floderDialog.currentFolder);
    }
    onRejected: {
        console.log("Canceled")
    }
    visible: false
}
