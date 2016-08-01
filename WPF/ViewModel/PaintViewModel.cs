using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using WPF.Infrastructure;

namespace WPF.ViewModel
{
    public class PaintViewModel
    {
        public DrawViewModel Draw { get; set; }

        public ToolBarViewModel ToolBar { get; set; }

        public System.Windows.Forms.UserControl OpenGLRenderControl { get; set; }

        public PaintViewModel()
        {
            this.Draw = new DrawViewModel();
            this.ToolBar = new ToolBarViewModel();
        }

    }
}
