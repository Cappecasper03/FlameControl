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

    public void BeginMoveWindow( object _, PointerPressedEventArgs args )
    {
        if( args.ClickCount == 1 )
            BeginMoveDrag( args );

        args.Handled = true;
    }

    public void MaximizeOrRestoreWindow( object _, TappedEventArgs args )
    {
        if( WindowState == WindowState.Maximized )
            WindowState = WindowState.Normal;
        else
            WindowState = WindowState.Maximized;

        args.Handled = true;
    }

    private void OnWindowBorderPointerPressed( object sender, PointerPressedEventArgs args )
    {
        if( sender is Border border && border.Tag is WindowEdge edge && CanResize )
            BeginResizeDrag( edge, args );
    }
}