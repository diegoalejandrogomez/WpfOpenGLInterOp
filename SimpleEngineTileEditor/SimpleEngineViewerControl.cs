using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    public class SimpleEngineViewerControl : UserControl
	{
        #region SimpleEngineImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleEngine_Instance();

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_Initialize();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_InitRenderer(IntPtr hWnd, UInt32 width, UInt32 height);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_InitInput(IntPtr hWnd, bool exclusive);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_SetGameLogic(IntPtr logic);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleRenderer_ResizeWindow(Int32 width, Int32 height);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_ScreenToWorld(ref Int32 x, ref Int32 y);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_Render(float dt);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_Advance(float dt);
        #endregion

        #region NativeEditorImports
        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern IntPtr TileEditorApp_Create();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_Destroy(IntPtr app);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorPosition(float  x, float y);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorIdle();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorTile(String sheet, Int32 index);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void NewMap();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void LoadState(String gameState);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern String GetState();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetMapSize(int width, int height);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetMapWidth(int width);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetMapHeight(int height);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetCursorPosition(float x, float y);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetCursorIdle();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetCursorTile(String sheet, int index);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void SetCursorErase();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void Paint();


        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern int GetMapWidth();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern int GetMapHeight();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern String Serialize();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern bool Deserialize(String node);
        #endregion

        public IntPtr WPFWindowHandle { get; set; }

        SimpleEngineViewerControl() {
            this.Load += OnLoad;
            this.SizeChanged += OnSizeChanged;
        }

        public void OnLoad(Object sender, EventArgs e) {

        }

        public void Initialize()
        {
            IntPtr hWnd = this.Handle;
            SimpleEngine_Instance();
            SimpleEngine_InitRenderer(hWnd, (UInt32)Width, (UInt32)Height);
            SimpleEngine_InitInput(WPFWindowHandle, false);
            SimpleEngine_Initialize();

            IntPtr appLogic = TileEditorApp_Create();
            SimpleEngine_SetGameLogic(appLogic);
            OnEngineInitialized(this, EventArgs.Empty);

        }

        public void OnSizeChanged(Object sender, EventArgs e) {
            SimpleRenderer_ResizeWindow(Width, Height);
        }

        public void SetMousePosition(float x, float y)
        {
            Int32 ix = (Int32)x;
            Int32 iy = (Int32)y;

            SimpleCamera2D_ScreenToWorld(ref ix, ref iy);               
            TileEditorApp_SetCursorPosition(ix, iy);
        }

        override protected void OnPaintBackground(PaintEventArgs e) {

        }

        override protected void OnPaint(PaintEventArgs e) {
            SimpleEngine_Advance(0.0f);
            SimpleEngine_Render(0.0f);
        }

        ManagedSimpleObject SetItem(float x, float y) {

            return null;
        }

        public void Restart() {
                       

        }

      

        public void MoveCamera(float dx, float dy) {

        }
        public void DeltaZoom(float dz) {

        }
        public float GetZoom() {
            return 0.0f;
        }
        public void SetZoom(float z) {
        }

        //System::Collections::Generic::List<ManagedSimpleObject^>^ GetAllTiles();

        //Custom events
        event EventHandler OnEngineInitialized;

                

    //    int MaxZoom
    //    {
    //    get() {
    //        SimpleScene* scene = SimpleEngine::Instance()->GetScene();
    //        if (scene != nullptr)
    //            return (int)scene->GetCamera()->GetMaxZoom();
    //        return 100;
    //    }
    //}

    //property System::Collections::Generic::List<ManagedSimpleLayer^>^ ManagedSimpleLayers
    //{
    //    System::Collections::Generic::List < ManagedSimpleLayer ^>^ get() {
    //        System::Collections::Generic::List < ManagedSimpleLayer ^>^ managedSimpleLayers =
    //            gcnew System::Collections::Generic::List < ManagedSimpleLayer ^> ();

    //        if (SimpleEngine::Instance()->GetScene() != nullptr)
    //        {
    //            std::vector<SimpleLayer*> simpleLayers = SimpleEngine::Instance()->GetScene()->GetLayers();


    //            if (simpleLayers.size() != 0)
    //            {
    //                for (auto* layer : simpleLayers)
    //                {
    //                    ManagedSimpleLayer ^ newManagedLayer = gcnew ManagedSimpleLayer(layer);
    //                    managedSimpleLayers->Add(newManagedLayer);
    //                }

    //            }
    //        }

    //        return managedSimpleLayers;
    //    };

    }
                
}
