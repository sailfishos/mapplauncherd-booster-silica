import QtQuick 2.0
import Sailfish.Silica 1.0

ApplicationWindow {
    cover: null  // don't create a cover - the switcher will try to show it
    BackgroundItem { }
    Button { }
    SilicaFlickable {
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
            CoverBackground { }
            CoverPlaceholder { }
            DatePicker { }
            Dialog {
                DialogHeader { }
            }
            DockedPanel { }
            Drawer { }
            IconButton { }
            SilicaListView {
                ScrollDecorator { }
                PushUpMenu { }
                ListItem { }
            }
            MenuItem { }
            Page { }
            RemorseItem { }
            RemorsePopup { }
            SearchField { }
            SectionHeader { }
            TextSwitch { }
            ValueButton { }
            ViewPlaceholder { }
        }
    }
}
