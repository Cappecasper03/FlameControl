using System;
using System.Linq;
using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Platform.Storage;
using FlameControl.Native;
using FlameControl.Views.Main;

namespace FlameControl.Views.Git;

public partial class Clone : Command
{
    public Clone( )
    {
        InitializeComponent();

        FileName    = Os.GitExecutable;
        CommandName = "clone";
    }

    protected override void BeginExecute( )
    {
        CommandArguments = $"{RemoteUrl.Text} {FolderName.Text}  -v --progress";

        if( ParentFolder.Text != null )
            WorkingDirectory = ParentFolder.Text;
    }

    private async void SelectFolder( object _, RoutedEventArgs args )
    {
        var options  = new FolderPickerOpenOptions { AllowMultiple = false };
        var toplevel = TopLevel.GetTopLevel( this );
        if( toplevel == null )
            return;

        var selected = await toplevel.StorageProvider.OpenFolderPickerAsync( options );
        if( selected.Count == 1 )
            ParentFolder.Text = selected[ 0 ].Path.LocalPath;

        args.Handled = true;
    }
}