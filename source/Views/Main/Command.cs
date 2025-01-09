using System;
using System.Diagnostics;
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
        try
        {
            BeginExecute();

            ProcessStartInfo processStartInfo = new ProcessStartInfo
            {
                FileName               = FileName,
                Arguments              = CommandName + " " + CommandArguments,
                WorkingDirectory       = WorkingDirectory,
                RedirectStandardOutput = true,
                UseShellExecute        = false,
                CreateNoWindow         = true,
            };

            Process process = new Process { StartInfo = processStartInfo };
            process.Start();

            while( !process.StandardOutput.EndOfStream )
                Console.WriteLine( await process.StandardOutput.ReadLineAsync() );

            await process.WaitForExitAsync();
        }
        catch( Exception e )
        {
            Console.WriteLine( e );
        }
    }
}