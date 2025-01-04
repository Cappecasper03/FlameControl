using System;
using System.Diagnostics;

namespace FlameControl.Native;

public static class Os
{
    public interface IBackend
    {
        string FindGitExecutable( );

        void OpenInFileManager( string path, bool select );
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

    public static async void ExecuteCommand( )
    {
        ProcessStartInfo processStartInfo = new ProcessStartInfo
        {
            FileName  = GitExecutable,
            Arguments = "init",
            // WorkingDirectory       = "",
            RedirectStandardOutput = true,
            RedirectStandardError  = true,
            UseShellExecute        = false,
            CreateNoWindow         = true,
        };

        Process process = new Process { StartInfo = processStartInfo };

        try
        {
            process.Start();
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();

            await process.WaitForExitAsync();
        }
        catch( Exception e )
        {
            Console.WriteLine( e );
        }
    }

    public static string FindGitExecutable( )
    {
        return Backend?.FindGitExecutable() ?? throw new InvalidOperationException();
    }

    public static void OpenInFileManager( string path, bool select = false )
    {
        Backend?.OpenInFileManager( path, select );
    }
}