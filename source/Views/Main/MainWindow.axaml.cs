using System;
using Avalonia.Controls;
using Avalonia.Interactivity;
using FlameControl.Views.Git;

namespace FlameControl.Views.Main;

public partial class MainWindow : ChromelessWindow
{
    public MainWindow( )
    {
        InitializeComponent();
    }

    private void ShowPopoutWindow( UserControl _window )
    {
        var window = new PopoutWindow( _window );
        window.ShowDialog( this );
    }

    public void ShowClonePopout( object _, RoutedEventArgs _args )
    {
        ShowPopoutWindow( new Clone() );
    }

    public void ShowInitPopout( object _, RoutedEventArgs _args )
    {
        ShowPopoutWindow( new Init() );
    }
}