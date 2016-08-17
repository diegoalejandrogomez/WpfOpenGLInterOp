﻿using Microsoft.Win32;
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
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using WPF.Infrastructure;
using WPF.Model;
using System.Collections;
using System.Runtime.Serialization.Json;

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
                openGLRenderControl.Resize += Resize;
                               
                
            }
        }

        private void Resize(object sender, EventArgs e)
        {
            ZoomLevel = _zoomLevel;
        }

        private void OnMouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            SimpleEngineViewerControl view = openGLRenderControl as SimpleEngineViewerControl;      
            ZoomLevel = (Int32) ((e.Delta * _zoomSpeed * 10.0f  + view.GetZoom()) / (float)MaxZoomLevel  * 100.0f);//conversion to zoom level;
      
        }

        private void OnGameLogicCreated(object sender, EventArgs e)
        {
            _tileMap = new TileMapControl();
            PropertyChanged(this, new PropertyChangedEventArgs("MaxZoomLevel"));
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

        private Int32 _zoomLevel;

        public Int32 ZoomLevel {

            get {
                return _zoomLevel;
            }
            set {
                SimpleEngineViewerControl view = openGLRenderControl as SimpleEngineViewerControl;
                _zoomLevel = value;
                _zoomLevel = Math.Max(Math.Min(100, (int)_zoomLevel), 0);    
                view.SetZoom(_zoomLevel / 100.0f*MaxZoomLevel);
                PropertyChanged(this, new PropertyChangedEventArgs("ZoomLevel"));
            }
        }

        
        public Int32 MaxZoomLevel
        {
            get {
                SimpleEngineViewerControl view = openGLRenderControl as SimpleEngineViewerControl;
                return view.MaxZoom;
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

        public bool Paint;

        public bool Erase;

        public bool Pick;

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

        public ObservableCollection<TileViewModel> Tiles { get; set; }

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
            this.Paint = false;
            this.Erase = false;
            this.Pick = false;        
            
        }

        public void OnClick(Object sender, EventArgs e)
        {
            if (Pick) //We should filter based on selected tool (brush, move tile, etc)
            {
                if (Selected != null)
                    Drag = false;
                int x = ((System.Windows.Forms.MouseEventArgs)e).X;
                int y = ((System.Windows.Forms.MouseEventArgs)e).Y;
                Selected = null;
                Selected = ((SimpleEngineViewerControl)OpenGLRenderControl).SetItem(x, y);
                if (Selected == null)
                    Selected = _tileMap;
            }else
            {
                ((SimpleEngineViewerControl)OpenGLRenderControl).Paint();               
                
            }
            PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
            PropertyChanged(this, new PropertyChangedEventArgs("MaxZoomLevel"));
        }
        #endregion

        #region Commands
        private ICommand setDrawLineCommand;

        private ICommand setDrawSquareCommand;

        private ICommand openFileCommand;

        private ICommand importImageCommand;

        private ICommand saveCommand;

        private ICommand addSelectedTile;

        private ICommand setDragCommand;

        private ICommand setPaintCommand;

        private ICommand setEraseCommand;

        private ICommand setPickCommand;

        private ICommand splitSelectedImage;

        private ICommand deleteSelectedTile;

        private ICommand deleteSelectedLayer;

        private ICommand editSelectedLayer;

        private ICommand addLayer;

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


        public static byte[] ConvertToBytes(BitmapImage bitmapImage)
        {
            byte[] data;
            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmapImage));
            using (MemoryStream ms = new MemoryStream())
            {
                encoder.Save(ms);
                data = ms.ToArray();
            }

            return data;
        }

        public ICommand AddSelectedTile
        {
            get
            {
                if (addSelectedTile == null)
                {
                    addSelectedTile = new Command((tile) =>
                    {
                        var tileObject = (TileViewModel)tile;
                        tileObject.SpriteControl.AddControl(tileObject.Path, tileObject.x, tileObject.y, tileObject.width, tileObject.heigth);
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
                        var tileObject = (TileViewModel)tile;
                        var image = tileObject.Image;
                        int width = (int)((BitmapImage)image).Width;
                        int heigth = (int)((BitmapImage)image).Height;
                        int x = 0;
                        int y = 0;

                        if (QuantityX == 0)
                            QuantityX = 1;
                        if (QuantityY == 0)
                            QuantityY = 1;

                        int proportionalWidth = width / QuantityX ;
                        int proportionalHeigth = heigth / QuantityY;

                        
                        while (y + proportionalHeigth <= heigth)
                        {
                            while (x + proportionalWidth <= width)
                            {
                                var imageSplited = BitmapImage2Bitmap((BitmapImage)image).Clone(new Rectangle(x, y, proportionalWidth, proportionalHeigth), System.Drawing.Imaging.PixelFormat.DontCare);
                                BitmapImage newImage = BitmapToImageSource(imageSplited);
                                var newTile = new TileViewModel();
                                newTile.Image = newImage;
                                newTile.Path = tileObject.Path;
                                newTile.x = x;
                                newTile.y = y;
                                newTile.width = proportionalWidth;
                                newTile.heigth = proportionalHeigth;                              
                                newTile.SpriteControl = new SpriteSheetControl();
                                newTile.Splited = true;
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
                        var tileObject = tile as TileViewModel;
                        if(tileObject != null)
                            Tiles.Remove(tileObject);
                    });
                }

                return deleteSelectedTile;
            }
        }

        public ICommand DeleteSelectedLayer
        {
            get
            {
                if (deleteSelectedLayer == null)
                {
                    deleteSelectedLayer = new Command((layer) =>
                    {
                        var layerObject = layer as ManagedSimpleLayer;
                        if (layerObject != null)
                        {
                            layerObject.Remove();
                            Layers.Remove(layerObject);
                            PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
                        }
                    });
                }

                return deleteSelectedLayer;
            }
        }



        public ICommand EditSelectedLayer
        {
            get
            {
                if (editSelectedLayer == null)
                {
                    editSelectedLayer = new Command((layer) =>
                    {
                        Window window = new Window
                        {
                            Title = "My User Control Dialog",
                            Content = new LayerEditor()
                        };

                        ((System.Windows.Controls.UserControl)window.Content).DataContext = layer;
                        window.Width = 300;
                        window.Height = 600;
                        window.Closed += Window_Closed;
                        window.ShowDialog();
                        
                    });
                }

                return editSelectedLayer;
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
        }

        public ICommand AddLayer
        {
            get
            {
                if (addLayer == null)
                {
                    addLayer = new Command((layer) =>
                    {
                        var layerObject = new ManagedSimpleLayer();
                        PropertyChanged(this, new PropertyChangedEventArgs("Layers"));
                    });
                }

                return addLayer;
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

        public ICommand SaveCommand
        {
            get
            {
                if (saveCommand == null)
                {
                    saveCommand = new Command((vm) =>
                    {
                        SaveFileDialog dialog = new SaveFileDialog();
                        dialog.DefaultExt = ".poc";
                        if (dialog.ShowDialog() == true)
                        {
                            var project = new Project();
                            var scene = new Scene();
                            foreach(var tile in Tiles)
                            {
                                var resource = new Resource();
                                resource.Name = tile.Path;
                                resource.Data = ConvertToBytes(tile.Image);
                                var property = new ResourceProperty();
                                property.Heigth = tile.heigth;
                                property.Width = tile.width;
                                property.X = tile.x;
                                property.Y = tile.y;
                                resource.Properties.Add(property);
                                project.Resources.Add(resource);   
                            }
                            /*
                            if (tile.Splited)
                            {
                                
                            }
                            else*/
                            foreach(var tile in ((SimpleEngineViewerControl)OpenGLRenderControl).GetAllTiles())
                            {
                                var tileScene = new Tile();
                                var property = new ResourceProperty();
                                property.Heigth = (int) tile.sizeH;
                                property.Width = (int)tile.sizeW;
                                property.X = (int)tile.positionX;
                                property.Y = (int)tile.positionY;
                                tileScene.Properties.Add(property);
                                scene.Tiles.Add(tileScene);
                            }

                            project.Scenes.Add(scene);

                            var json = Newtonsoft.Json.JsonConvert.SerializeObject(project);
                            System.IO.File.WriteAllText(dialog.FileName, json);

                        }
                    });
                }

                return saveCommand;
            }
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
                            BitmapImage bitmapImage = null;
                            var json = System.IO.File.ReadAllText(dialog.FileName);
                            var project = Newtonsoft.Json.JsonConvert.DeserializeObject<Project>(json);
                            int i = 1;
                            string path = string.Empty;
                            foreach (var item in project.Resources)
                            {
                                byte[] image = item.Data;
                                MemoryStream ms = new MemoryStream(image);
                                System.Drawing.Image img = System.Drawing.Image.FromStream(ms);
                                

                                if (i == 1)
                                {
                                    path = AppDomain.CurrentDomain.BaseDirectory + @"/temp/image" + i + ".png";
                                    Directory.CreateDirectory(AppDomain.CurrentDomain.BaseDirectory + @"/temp");

                                    img.Save(path);
                                }

                                i++;
                                var newTile = new TileViewModel();
                                
                                newTile.Path = path;
                                if(item.Properties.Any())
                                {
                                    newTile.x = item.Properties.FirstOrDefault().X;
                                    newTile.y = item.Properties.FirstOrDefault().Y;
                                    newTile.width = (int)item.Properties.FirstOrDefault().Width;
                                    newTile.heigth = (int)item.Properties.FirstOrDefault().Heigth;
                                }

                                if (i > 2)
                                {
                                    if(bitmapImage != null)
                                    {
                                        var imageSplited = BitmapImage2Bitmap((BitmapImage)bitmapImage).Clone(new Rectangle(newTile.x, newTile.y, newTile.width, newTile.heigth), System.Drawing.Imaging.PixelFormat.DontCare);
                                        newTile.Image = BitmapToImageSource(imageSplited);
                                        newTile.Splited = true;
                                    }
                                }
                                else
                                {
                                    newTile.Image = new BitmapImage(new Uri(path));
                                    bitmapImage = newTile.Image;
                                }

                                newTile.SpriteControl = new SpriteSheetControl();
                                if (Tiles == null)
                                    Tiles = new ObservableCollection<TileViewModel>();
                                this.Tiles.Add(newTile);
                            }

                            PropertyChanged(this, new PropertyChangedEventArgs("Tiles"));

                            foreach (var scene in project.Scenes)
                            {
                                foreach(var tile in scene.Tiles)
                                {
                                   /* var x = tile.Properties.FirstOrDefault().X;
                                    var y = tile.Properties.FirstOrDefault().Y;
                                    var tileObject = this.Tiles[5];
                                    tileObject.SpriteControl.AddControl(tileObject.Path, tileObject.x, tileObject.y, tileObject.width, tileObject.heigth);*/
                                }

                            }
                        }
                    });
                }

                return openFileCommand;
            }
        }
        

        public ICommand ImportImageCommand
        {
            get
            {
                if (importImageCommand == null)
                {
                    importImageCommand = new Command((vm) =>
                    {
                        OpenFileDialog dialog = new OpenFileDialog();
                        if (dialog.ShowDialog() == true)
                        {
                            this.FilePath = dialog.FileName;
                            var newTile = new TileViewModel();
                            newTile.Image = new BitmapImage(new Uri(this.FilePath));
                            newTile.Path = this.FilePath;
                            newTile.x = 0;
                            newTile.y = 0;
                            newTile.width = (int)newTile.Image.Width;
                            newTile.heigth = (int)newTile.Image.Height;
                            newTile.SpriteControl = new SpriteSheetControl();                         
                            if (Tiles == null)
                                Tiles = new ObservableCollection<TileViewModel>();
                            this.Tiles.Add(newTile);

                            PropertyChanged(this, new PropertyChangedEventArgs("Tiles"));
                        }
                    });
                }

                return importImageCommand;
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


        public ICommand SetPaintCommand
        {
            get
            {
                if (setPaintCommand == null)
                {

                    setPaintCommand = new Command((vm) =>
                    {
                        var originalpaint = Paint;
                        ClearParameters();
                        Paint = !originalpaint;
                        _tileMap.IdleBrush();                        
                    });
                }

                return setPaintCommand;
            }
            set { }
        }

        public ICommand SetEraseCommand
        {
            get
            {
                if (setEraseCommand == null)
                {

                    setEraseCommand = new Command((vm) =>
                    {
                        var originalerase = Erase;
                        ClearParameters();
                        Erase = !originalerase;
                        _tileMap.EraseBrush();
                    });
                }

                return setEraseCommand;
            }
            set { }
        }
        public ICommand SetPickCommand
        {
            get
            {
                if (setPickCommand == null)
                {

                    setPickCommand = new Command((vm) =>
                    {
                        var originalpick = Pick;
                        ClearParameters();
                        Pick= !originalpick;
                        _tileMap.IdleBrush();
                    });
                }

                return setPickCommand;
            }
            set { }
        }

        public ManagedSimpleLayer SelectedLayer { get; set; }

        #endregion
    }
}
