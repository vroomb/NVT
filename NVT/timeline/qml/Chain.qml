import QtQuick
import QtQuick.Shapes
import NVT.Timeline

TimelineChain {
    id: root

    onPathChanged: {
        pathPolyline.path = root.path;
    }

    onStrokeWidthChanged: {
        shapePathPolyline.strokeWidth = root.strokeWidth
    }

    Shape {
        id: shape
        ShapePath {
            id: shapePathPolyline
            strokeColor: "white"
            strokeWidth: root.strokeWidth
            fillColor: "transparent"

            PathPolyline {
                id: pathPolyline
            }
        }
        Component.onCompleted: {}
    }
}
