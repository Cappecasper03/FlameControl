using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.VisualTree;

namespace FlameControl.Views.Main;

public partial class PopoutWindow : ChromelessWindow
{
    private readonly Command? _command;

    public PopoutWindow( )
    {
        InitializeComponent();
    }

    public PopoutWindow( UserControl userContent )
    {
        InitializeComponent();

        var grid = Content as Grid;

        if( grid?.Children[ 1 ] is not ContentControl content )
            return;

        _command        = userContent as Command;
        content.Content = _command;
    }

    private void ExecuteAndCloseWindow( object _, RoutedEventArgs args )
    {
        _command?.Execute();
        Close();

        args.Handled = true;
    }

    private void CloseWindow( object _, RoutedEventArgs args )
    {
        Close();

        args.Handled = true;
    }
}