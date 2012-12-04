import QtQuick 1.1
import com.jolla.components 1.0

ApplicationWindow {
    BackgroundItem { }
    Button { }
    JollaFlickable {
        PullDownMenu { } // creates HighlightFeedback.qml and initializes sampleCache
    }
    Label { }
    PageHeader { }
    Slider { }
    Switch { }
    TextArea { }
    TextField { }
    Component {
        // These will be compiled but not instantiated.
        // If instantiation won't result in further caching then place those
        // components here.
        Item {
            ComboBox { }
            ContextMenu { }
            Dialog { }
            JollaListView {
                ScrollDecorator { }
                PushUpMenu { }
            }
            MenuItem { }
            Page { }
            ToolIcon { }
        }
    }
}
