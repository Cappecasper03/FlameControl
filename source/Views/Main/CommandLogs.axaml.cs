using System.Threading.Tasks;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Input;
using Avalonia.Interactivity;

namespace FlameControl.Views.Main;

public partial class CommandLogs : UserControl
{
    private readonly Popup   _popup;
    private          Window? _window;

    public CommandLogs( )
    {
        InitializeComponent();

        _popup = new Popup
        {
            PlacementTarget = this,
            IsOpen          = false,
            IsVisible       = true,
            Width           = 600,
            Height          = 400,
        };
    }

    public void OpenPopout( object _, RoutedEventArgs args )
    {
        _popup.IsOpen = true;

        if( _window != null )
            return;

        Window? window = GetMainWindow();
        if( window == null )
            return;

        _window = window;
        _window.AddHandler( PointerPressedEvent, OutsideClickHandler, handledEventsToo: true );
    }

    private void OutsideClickHandler( object? sender, PointerPressedEventArgs args )
    {
        if( !_popup.IsOpen )
            return;

        if( !_popup.Bounds.Contains( args.GetPosition( null ) ) )
            _popup.IsOpen = false;
    }

    private Window? GetMainWindow( )
    {
        var parent = Parent;
        while( parent != null )
        {
            if( parent is Window window )
            {
                return window;
            }

            parent = parent.Parent;
        }

        return null;
    }
}