using Avalonia.Controls;

namespace FlameControl.Views.Git;

public partial class Repository : UserControl
{
    public FlatTreeDataGridSource< string > CommitHistory { get; set; }

    public Repository( )
    {
        InitializeComponent();
    }
}