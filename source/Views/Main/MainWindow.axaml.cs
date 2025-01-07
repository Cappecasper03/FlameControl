using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using FlameControl.Views.Git;

namespace FlameControl.Views.Main;

public partial class MainWindow : ChromelessWindow
{
    public MainWindow( )
    {
        InitializeComponent();
    }

    private void ShowPopoutWindow( UserControl userWindow )
    {
        var window = new PopoutWindow( userWindow );
        window.ShowDialog( this );
    }

    public void ShowClonePopout( object _, RoutedEventArgs args )
    {
        ShowPopoutWindow( new Clone() );
    }

    public void ShowInitPopout( object _, RoutedEventArgs args )
    {
        ShowPopoutWindow( new Init() );
    }
}