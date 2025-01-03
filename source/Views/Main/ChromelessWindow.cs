using System;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Platform;

namespace FlameControl.Views.Main;

public class ChromelessWindow : Window
{
    protected ChromelessWindow( )
    {
        if( OperatingSystem.IsWindows() )
        {
            ExtendClientAreaChromeHints       = ExtendClientAreaChromeHints.NoChrome;
            ExtendClientAreaToDecorationsHint = true;
        }
        else
        {
            ExtendClientAreaChromeHints       = ExtendClientAreaChromeHints.SystemChrome;
            ExtendClientAreaToDecorationsHint = true;
        }
    }

    public void BeginMoveWindow( object _, PointerPressedEventArgs _args )
    {
        if( _args.ClickCount == 1 )
            BeginMoveDrag( _args );

        _args.Handled = true;
    }

    public void MaximizeOrRestoreWindow( object _, TappedEventArgs _args )
    {
        if( WindowState == WindowState.Maximized )
            WindowState = WindowState.Normal;
        else
            WindowState = WindowState.Maximized;

        _args.Handled = true;
    }

    private void OnWindowBorderPointerPressed( object _sender, PointerPressedEventArgs _args )
    {
        if( _sender is Border border && border.Tag is WindowEdge edge && CanResize )
            BeginResizeDrag( edge, _args );
    }
}