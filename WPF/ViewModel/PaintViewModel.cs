using Microsoft.Win32;
using SimpleEngineControls;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using WPF.Infrastructure;
using WPF.Model;

namespace WPF.ViewModel
{
    public class PaintViewModel: INotifyPropertyChanged
    {
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
                (openGLRenderControl as SimpleEngineViewerControl).OnEngineInitialized += OnGameLogicCreated;
                openGLRenderControl.MouseWheel += OnMouseWheel;
                PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
               
                
            }
        }

        private void OnMouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            SimpleEngineViewerControl view = openGLRenderControl as SimpleEngineViewerControl;
            view.DeltaZoom(e.Delta * _zoomSpeed);
      
        }

        private void OnGameLogicCreated(object sender, EventArgs e)
        {
            _tileMap = new TileMapControl();
        }

        public void OnDrag(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            SimpleEngineViewerControl view = openGLRenderControl as SimpleEngineViewerControl;

            //Panning
            if (e.Button == System.Windows.Forms.MouseButtons.Right)               
                view.MoveCamera(-(e.X - _prevX) * _panSpeed, (e.Y - _prevY) * _panSpeed );               
            

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

            _prevX = e.X;
            _prevY = e.Y;

            //Update cursor position
            view.SetMousePosition(e.X, e.Y);
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


        private int quantityX;

        public int QuantityX
        {
            get { return quantityX; }
            set
            {
                quantityX = value;
                PropertyChanged(this, new PropertyChangedEventArgs("QuantityX"));
            }
        }

        private int quantityY;

        public int QuantityY
        {
            get { return quantityY; }
            set
            {
                quantityY = value;
                PropertyChanged(this, new PropertyChangedEventArgs("QuantityY"));
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

        public List<ManagedSimpleLayer> Layers
        {
            get
            {
                return ((SimpleEngineViewerControl)OpenGLRenderControl).ManagedSimpleLayers;
            }

        }

        public ObservableCollection<Tile> Tiles { get; set; }

        TileMapControl _tileMap;
        float _panSpeed = 1.0f;
        float _zoomSpeed = 0.005f;
        float _prevX, _prevY;
        

        #endregion

        #region Methods
        public void ClearParameters()
        {
            this.DrawSquare = false;
            this.DrawLine = false;
            this.Drag = false;
        }

        public void OnClick(Object sender, EventArgs e)
        {

            if (Selected != null)
                Drag = false;
            int x = ((System.Windows.Forms.MouseEventArgs)e).X;
            int y = ((System.Windows.Forms.MouseEventArgs)e).Y;
            Selected = null;
            Selected = ((SimpleEngineViewerControl)OpenGLRenderControl).SetItem(x, y);
            if (Selected == null)
                Selected = _tileMap;

            PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
        }
        #endregion

        #region Commands
        private ICommand setDrawLineCommand;

        private ICommand setDrawSquareCommand;

        private ICommand openFileCommand;

        private ICommand addSelectedTile;

        private ICommand setDragCommand;

        private ICommand splitSelectedImage;

        private ICommand deleteSelectedTile;

        public event PropertyChangedEventHandler PropertyChanged = delegate(object sender, PropertyChangedEventArgs e)
        {
            var paintViewModel = sender as PaintViewModel;

            if (paintViewModel.OpenGLRenderControl != null)
            {
                //todo get this info using something better than reflection
                //paintViewModel.OpenGLRenderControl.SetProperty(e.PropertyName, true);
            }
        };

        BitmapImage BitmapToImageSource(Bitmap bitmap)
        {
            using (MemoryStream memory = new MemoryStream())
            {
                bitmap.Save(memory, System.Drawing.Imaging.ImageFormat.Bmp);
                memory.Position = 0;
                BitmapImage bitmapimage = new BitmapImage();
                bitmapimage.BeginInit();
                bitmapimage.StreamSource = memory;
                bitmapimage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapimage.EndInit();

                return bitmapimage;
            }
        }

        private Bitmap BitmapImage2Bitmap(BitmapImage bitmapImage)
        {
            // BitmapImage bitmapImage = new BitmapImage(new Uri("../Images/test.png", UriKind.Relative));

            using (MemoryStream outStream = new MemoryStream())
            {
                BitmapEncoder enc = new BmpBitmapEncoder();
                enc.Frames.Add(BitmapFrame.Create(bitmapImage));
                enc.Save(outStream);
                System.Drawing.Bitmap bitmap = new System.Drawing.Bitmap(outStream);

                return new Bitmap(bitmap);
            }
        }

        public ICommand AddSelectedTile
        {
            get
            {
                if (addSelectedTile == null)
                {
                    addSelectedTile = new Command((tile) =>
                    {
                        var tileObject = (Tile)tile;
                        tileObject.SpriteControl.AddControl(tileObject.Path);
                    });
                }

                return addSelectedTile;
            }
        }

        public ICommand SplitSelectedImage
        {
            get
            {
                if (splitSelectedImage == null)
                {

                    splitSelectedImage = new Command((tile) =>
                    {
                        var tileObject = (Tile)tile;
                        var image = tileObject.Image;
                        int width = (int)((BitmapImage)image).Width;
                        int heigth = (int)((BitmapImage)image).Height;
                        int x = 0;
                        int y = 0;
                        int proportionalWidth = width / QuantityX ;
                        int proportionalHeigth = heigth / QuantityY;

                        
                        while (y + proportionalHeigth <= heigth)
                        {
                            while (x + proportionalWidth <= width)
                            {
                                var asd = BitmapImage2Bitmap((BitmapImage)image).Clone(new Rectangle(x, y, proportionalWidth, proportionalHeigth), System.Drawing.Imaging.PixelFormat.DontCare);
                                BitmapImage newImage = BitmapToImageSource(asd);
                                var newTile = new Tile();
                                newTile.Image = newImage;
                                newTile.Path = tileObject.Path;
                                newTile.SpriteControl = new SpriteSheetControl();
                                newTile.SpriteControl.positionX = x;
                                newTile.SpriteControl.positionY = y;
                                newTile.SpriteControl.width = proportionalWidth;
                                newTile.SpriteControl.heigth = proportionalHeigth;
                                Tiles.Add(newTile);
                                PropertyChanged(this, new PropertyChangedEventArgs("Tiles"));
                                x += proportionalWidth;
                            }

                            x = 0;
                            y += proportionalHeigth;
                        }
                    });
                }

                return splitSelectedImage;
            }

            set { }
        }

        public ICommand DeleteSelectedTile
        {
            get
            {
                if (deleteSelectedTile == null)
                {
                    deleteSelectedTile = new Command((tile) =>
                    {
                        var tileObject = tile as Tile;
                        if(tileObject != null)
                            Tiles.Remove(tileObject);
                    });
                }

                return deleteSelectedTile;
            }
        }
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
                            var newTile = new Tile();
                            newTile.Image = new BitmapImage(new Uri(this.FilePath));
                            newTile.Path = this.FilePath;
                            newTile.SpriteControl = new SpriteSheetControl();
                            newTile.SpriteControl.positionX = 0;
                            newTile.SpriteControl.positionY = 0;
                            newTile.SpriteControl.width = (int)newTile.Image.Width;
                            newTile.SpriteControl.heigth = (int)newTile.Image.Height;
                            if (Tiles == null)
                                Tiles = new ObservableCollection<Tile>();
                            this.Tiles.Add(newTile);

                            PropertyChanged(this, new PropertyChangedEventArgs("Tiles"));
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
