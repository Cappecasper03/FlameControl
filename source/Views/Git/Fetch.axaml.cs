using FlameControl.Native;
using FlameControl.Views.Main;

namespace FlameControl.Views.Git;

public partial class Fetch : Command
{
    public Fetch( )
    {
        InitializeComponent();

        FileName    = Os.GitExecutable;
        CommandName = "fetch";
    }
}