using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using Avalonia.Controls;

namespace FlameControl.Views.Main;

public class Command : UserControl
{
    protected string FileName         { get; init; } = string.Empty;
    protected string CommandName      { get; init; } = string.Empty;
    protected string CommandArguments { get; set; }  = string.Empty;
    protected string WorkingDirectory { get; set; }  = string.Empty;

    protected Command( )
    {
    }

    protected virtual void BeginExecute( )
    {
    }

    public async void Execute( )
    {
        BeginExecute();

        ProcessStartInfo processStartInfo = new ProcessStartInfo
        {
            FileName               = FileName,
            Arguments              = $"{CommandName} {CommandArguments}",
            WorkingDirectory       = WorkingDirectory,
            RedirectStandardOutput = true,
            UseShellExecute        = false,
            CreateNoWindow         = true,
        };

        Console.WriteLine( $"Command: {processStartInfo.Arguments}" );

        Process process = new Process { StartInfo = processStartInfo };
        process.Start();

        var outputTask = Task.Run( async ( ) =>
        {
            while( await process.StandardOutput.ReadLineAsync() is { } line )
                Console.WriteLine( line );
        } );

        await Task.WhenAll( outputTask );
    }
}