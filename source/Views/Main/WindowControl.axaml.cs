using Avalonia;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.VisualTree;

namespace FlameControl.Views.Main;

public partial class WindowControl : UserControl
{
    public static readonly StyledProperty< bool > IsCloseButtonOnlyProperty =
        AvaloniaProperty.Register< WindowControl, bool >( nameof( IsCloseButtonOnly ) );

    public bool IsCloseButtonOnly
    {
        get => GetValue( IsCloseButtonOnlyProperty );
        set => SetValue( IsCloseButtonOnlyProperty, value );
    }

    public WindowControl( )
    {
        InitializeComponent();
    }

    private void MinimizeWindow( object _, RoutedEventArgs args )
    {
        var window = this.FindAncestorOfType< Window >();
        if( window != null )
            window.WindowState = WindowState.Minimized;

        args.Handled = true;
    }

    private void MaximizeOrRestoreWindow( object _, RoutedEventArgs args )
    {
        var window = this.FindAncestorOfType< Window >();
        if( window != null )
            window.WindowState = window.WindowState == WindowState.Maximized ? WindowState.Normal : WindowState.Maximized;

        args.Handled = true;
    }

    private void CloseWindow( object _, RoutedEventArgs args )
    {
        var window = this.FindAncestorOfType< Window >();
        window?.Close();

        args.Handled = true;
    }
}