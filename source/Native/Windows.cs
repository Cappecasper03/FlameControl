using System;
using System.IO;

namespace FlameControl.Native;

public class Windows : Os.IBackend
{
    public string FindGitExecutable( )
    {
        string? pathEnv = Environment.GetEnvironmentVariable( "PATH" );

        if( pathEnv == null )
            return string.Empty;

        foreach( string dir in pathEnv.Split( ';' ) )
        {
            string gitPath = Path.Combine( dir.Trim(), "git.exe" );
            if( File.Exists( gitPath ) )
                return gitPath;
        }

        return string.Empty;
    }
}