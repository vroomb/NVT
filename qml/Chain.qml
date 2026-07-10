import QtQuick
import QtQuick.Shapes
import NVTModule

TimelineChain {
    id: root

    onPathChanged: {
        pathPolyline.path = root.path
    }

    Shape {
        id: shape
        ShapePath {
            id: shapePathPolyline
            strokeColor: "white"
            strokeWidth: 16
            fillColor: "transparent"

            PathPolyline {
                id: pathPolyline
            }
        }
        Component.onCompleted: {
            //timelineGraph.update_vertices(red.x + parent.offset, red.y + parent.offset, green.x + parent.offset, green.y + parent.offset)
        }
    }
}
