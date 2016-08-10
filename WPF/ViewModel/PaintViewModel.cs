using Microsoft.Win32;
using SimpleEngineControls;
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
    public class PaintViewModel: INotifyPropertyChanged
    {

        public void OnClick(Object sender, EventArgs e)
        {
            
            int x = ((System.Windows.Forms.MouseEventArgs)e).X;
            int y = ((System.Windows.Forms.MouseEventArgs)e).Y;
            Selected = null;
            Selected = ((SimpleEngineViewerControl)OpenGLRenderControl).SetItem(x, y);
        }

        #region Properties

        private System.Windows.Forms.UserControl openGLRenderControl;
        public System.Windows.Forms.UserControl OpenGLRenderControl
        {
            get
            {
                return openGLRenderControl;
            }
            set
            {
                openGLRenderControl = value;
                openGLRenderControl.Click += new EventHandler(this.OnClick);
                openGLRenderControl.MouseMove += new System.Windows.Forms.MouseEventHandler(this.OnDrag);
            }
        }
        
        public void OnDrag(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            MousePosition = e.Location.X + ":" + e.Location.Y;
            if (this.Drag && Selected != null)
            {
                //Check if can be dragged ie ManagedSimpleObject
                ManagedSimpleObject sel = Selected as ManagedSimpleObject;
                if(sel != null) { 
                    sel.positionX = e.Location.X;
                    sel.positionY = e.Location.Y;
                }
                //Selected = null;
                //Selected = ((SimpleEngineViewerControl)OpenGLRenderControl).SetItem(e.Location.X, e.Location.Y);
            }
        }

        private String mousePosition;

        public String MousePosition
        {
            get
            {
                return mousePosition;
            }
            set
            {
                mousePosition = value;
                PropertyChanged(this, new PropertyChangedEventArgs("MousePosition"));
            }
        }
            

        public Object selected;
        public Object Selected
        {
            get
            {
                return selected;
            }
            set
            {
                selected = value;
                PropertyChanged(this, new PropertyChangedEventArgs("Selected"));
            }
        }

        

        public bool drawLine;

        public bool DrawLine
        {
            get { return drawLine; }
            set
            {
                drawLine = value;
                PropertyChanged(this, new PropertyChangedEventArgs("DrawLine"));
            }
        }


        public string color;

        public string Color
        {
            get { return color; }
            set
            {
                color = value;
                PropertyChanged(this, new PropertyChangedEventArgs("Color"));
            }
        }

        public string fps;

        public string Fps
        {
            get { return fps; }
            set
            {
                fps = value;
                PropertyChanged(this, new PropertyChangedEventArgs("Fps"));
            }
        }

        public bool DrawSquare;

        public bool Drag;

        public string filePath;

        public string FilePath
        {
            get { return filePath; }
            set
            {
                filePath = value;
                PropertyChanged(this, new PropertyChangedEventArgs("FilePath"));
            }
        }
        #endregion

        #region Methods
        public void ClearParameters()
        {
            this.DrawSquare = false;
            this.DrawLine = false;
            this.Drag = false;
        }

        #endregion

        #region Commands
        private ICommand setDrawLineCommand;

        private ICommand setDrawSquareCommand;

        private ICommand openFileCommand;

        private ICommand setDragCommand;

        public event PropertyChangedEventHandler PropertyChanged = delegate(object sender, PropertyChangedEventArgs e)
        {
            var paintViewModel = sender as PaintViewModel;

            if (paintViewModel.OpenGLRenderControl != null)
            {
                //todo get this info using something better than reflection
                //paintViewModel.OpenGLRenderControl.SetProperty(e.PropertyName, true);
            }
        };

        public ICommand SetDrawLineCommand
        {
            get
            {
                if (setDrawLineCommand == null)
                {

                    setDrawLineCommand = new Command((vm) =>
                    {
                        var originalDrawLine = DrawLine;
                        ClearParameters();
                        DrawLine = !originalDrawLine;
                    });
                }

                return setDrawLineCommand;
            }

            set { }
        }

        public ICommand SetDrawSquareCommand
        {
            get
            {
                if (setDrawSquareCommand == null)
                {

                    setDrawSquareCommand = new Command((vm) =>
                    {
                        var originalDrawSquare = DrawSquare;
                        ClearParameters();
                        DrawSquare = !originalDrawSquare;
                    });
                }

                return setDrawSquareCommand;
            }

            set { }
        }

        public ICommand OpenFileCommand
        {
            get
            {
                if (openFileCommand == null)
                {
                    openFileCommand = new Command((vm) =>
                    {
                        OpenFileDialog dialog = new OpenFileDialog();
                        if (dialog.ShowDialog() == true)
                        {
                            this.FilePath = dialog.FileName;
                            var spriteControl = new SpriteControl();

                            spriteControl.AddControl(this.FilePath);
                        }
                    });
                }

                return openFileCommand;
        }

            set { }
        }

        public ICommand SetDragCommand
        {
            get
            {
                if (setDragCommand == null)
                {

                    setDragCommand = new Command((vm) =>
                    {
                        var originaldrag = Drag;
                        ClearParameters();
                        Drag = !originaldrag;
                    });
                }

                return setDragCommand;
            }

            set { }
        }
        
        #endregion
    }
}
