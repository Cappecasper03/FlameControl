namespace FlameControl.Native;

public class Linux : Os.IBackend
{
    public string FindGitExecutable( )
    {
        throw new System.NotImplementedException();
    }

    public void OpenInFileManager( string path, bool select )
    {
        throw new System.NotImplementedException();
    }
}