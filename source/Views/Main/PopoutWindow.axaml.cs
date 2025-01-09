using Avalonia.Controls;

namespace FlameControl.Views.Main;

public partial class PopoutWindow : ChromelessWindow
{
    public PopoutWindow( )
    {
        InitializeComponent();
    }

    public PopoutWindow( UserControl userContent )
    {
        InitializeComponent();

        var grid = Content as Grid;

        if( grid?.Children[ 1 ] is ContentControl content )
            content.Content = userContent;
    }
}