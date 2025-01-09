using Avalonia.Controls;
using Avalonia.Interactivity;
using FlameControl.Native;
using FlameControl.Views.Main;

namespace FlameControl.Views.Git;

public partial class Init : Command
{
    public Init( )
    {
        InitializeComponent();

        FileName         = Os.GitExecutable;
        CommandName      = "init";
        WorkingDirectory = "C:/Users/Cappo/Downloads/test";
    }
}