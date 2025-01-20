using FlameControl.Native;
using FlameControl.Views.Main;

namespace FlameControl.Views.Git;

public class Log : Command
{
    public Log( )
    {
        FileName    = Os.GitExecutable;
        CommandName = "log";
    }
}