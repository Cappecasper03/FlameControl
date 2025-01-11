using System;
using System.Diagnostics;
using FlameControl.Views.Main;

namespace FlameControl.Native;

public static class Os
{
    public interface IBackend
    {
        string FindGitExecutable( );
    }

    public static string GitExecutable { get; set; }

    private static readonly IBackend? Backend = null;

    static Os( )
    {
        if( OperatingSystem.IsWindows() )
            Backend = new Windows();
        else if( OperatingSystem.IsLinux() )
            Backend = new Linux();
        else
            throw new Exception( "Platform not supported" );

        GitExecutable = Backend.FindGitExecutable();
    }

    public static string FindGitExecutable( )
    {
        return Backend?.FindGitExecutable() ?? throw new InvalidOperationException();
    }
}