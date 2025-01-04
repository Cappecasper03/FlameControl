using Avalonia.Controls;

namespace FlameControl.Views.Main;

public partial class PopoutWindow : ChromelessWindow
{
    public PopoutWindow( )
    {
        InitializeComponent();
    }

    public PopoutWindow( UserControl _content )
    {
        InitializeComponent();

        var grid  = Content as StackPanel;
        var child = grid?.Children[ 0 ] as Grid;

        if( child?.Children[ 1 ] is ContentControl content )
            content.Content = _content;
    }
}