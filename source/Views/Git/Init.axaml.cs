using System;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Platform.Storage;
using FlameControl.Native;
using FlameControl.Views.Main;

namespace FlameControl.Views.Git;

public partial class Init : Command
{
    public Init( )
    {
        InitializeComponent();

        FileName    = Os.GitExecutable;
        CommandName = "init";
    }

    protected override void BeginExecute( )
    {
        if( Folder.Text != null )
            WorkingDirectory = Folder.Text;
    }

    private async void SelectFolder( object _, RoutedEventArgs args )
    {
        try
        {
            var options  = new FolderPickerOpenOptions { AllowMultiple = false };
            var toplevel = TopLevel.GetTopLevel( this );
            if( toplevel == null )
                return;

            var selected = await toplevel.StorageProvider.OpenFolderPickerAsync( options );
            if( selected.Count == 1 )
                Folder.Text = selected[ 0 ].Path.LocalPath;

            args.Handled = true;
        }
        catch( Exception e )
        {
            Console.WriteLine( e );
        }
    }
}