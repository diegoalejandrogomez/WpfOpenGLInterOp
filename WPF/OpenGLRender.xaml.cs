using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using WPFOpenGLLib;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows.Forms;
using System.Windows.Interop;
using SimpleEngineTileEditor;

namespace WPF
{
    /// <summary>
    /// Interaction logic for OpenGLRender.xaml
    /// </summary>
    public partial class OpenGLRender : System.Windows.Controls.UserControl
    {

        private System.Windows.Threading.DispatcherTimer updateTimer;

        public bool DrawLine { get; set; }

        public System.Windows.Forms.UserControl OpenGLControl { get; set; }

        public int Ticks = 16000;
        int total = 0;
        public override void EndInit()
        {
            base.EndInit();
            //in Design mode
            
        }

        public OpenGLRender()
        {
            InitializeComponent();
            updateTimer = new System.Windows.Threading.DispatcherTimer(System.Windows.Threading.DispatcherPriority.Render);
            updateTimer.Interval = new TimeSpan(Ticks);
            updateTimer.Tick += new EventHandler(UpdateTimer_Tick);
            updateTimer.Start();
            Loaded += OpenGLRender_Loaded;
        }

        private void OpenGLRender_Loaded(object sender, RoutedEventArgs e)
        {
            OpenGLControl = OpenGLControl == null ? new SimpleEngineViewerControl() : OpenGLControl;
            DataContext = OpenGLControl;
            host.Child = OpenGLControl;
            //So we have a valid hwnd
            IntPtr windowHandle = new WindowInteropHelper(System.Windows.Application.Current.MainWindow).Handle;
            (OpenGLControl as SimpleEngineViewerControl).WPFWindowHandle = windowHandle;
            (OpenGLControl as SimpleEngineViewerControl).Initialize();

        }

        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            host.Child.Invalidate();
            host.Child.Refresh();
        
        }
    }
}
