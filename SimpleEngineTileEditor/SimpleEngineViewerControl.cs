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
        static extern void SimpleEngine_Shutdown();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_InitRenderer(IntPtr hWnd, UInt32 width, UInt32 height);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_InitInput(IntPtr hWnd, bool exclusive);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_SetGameLogic(IntPtr logic);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_Render(float dt);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_Advance(float dt);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleEngine_GetScene();
        #endregion

        #region SimpleRendererImports
        //Simple Renderer Imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleRenderer_ResizeWindow(Int32 width, Int32 height);
        #endregion

        #region SimpleCameraImports
        //Simple Camera Imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_ScreenToWorld(ref Int32 x, ref Int32 y);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_Move(float dx, float dy);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_DeltaZoom(float dz);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern float SimpleCamera2D_GetZoom();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern float SimpleCamera2D_GetMaxZoom();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_SetZoom(float zoom);
        #endregion

        #region SimpleSceneImports
        //Simple Scene Imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleScene_PickFirstPoint(float x, float y);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern UInt32 SimpleScene_GetLayerCount();

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleScene_GetLayerWithIdx(Int32 nLayer);

        #endregion

        #region SimpleLayerImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesBegin(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesNext(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesEnd(IntPtr layer);

        #endregion

        #region NativeEditorImports
        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern IntPtr TileEditorApp_Create();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_Destroy(IntPtr app);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorPosition(float x, float y);

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

        SimpleEngineViewerControl()
        {
            this.Load += OnLoad;
            this.SizeChanged += OnSizeChanged;
        }

        public void OnLoad(Object sender, EventArgs e)
        {

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

        public void OnSizeChanged(Object sender, EventArgs e)
        {
            SimpleRenderer_ResizeWindow(Width, Height);
        }

        public void SetMousePosition(float x, float y)
        {
            Int32 ix = (Int32)x;
            Int32 iy = (Int32)y;

            SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
            TileEditorApp_SetCursorPosition(ix, iy);
        }

        override protected void OnPaintBackground(PaintEventArgs e)
        {

        }

        override protected void OnPaint(PaintEventArgs e)
        {
            SimpleEngine_Advance(0.0f);
            SimpleEngine_Render(0.0f);
        }

        ManagedSimpleObject SetItem(float x, float y)
        {

            Int32 ix = (Int32)x;
            Int32 iy = (Int32)y;

            SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
            IntPtr res = SimpleScene_PickFirstPoint(x, y);

            if (res != IntPtr.Zero)
            {
                ManagedSimpleObject SelectedObject = new ManagedSimpleObject();
                SelectedObject.SetSimpleObject(res);
                return SelectedObject;
            }

            return null;
        }

        List<ManagedSimpleObject> GetAllTiles()
        {
            List<ManagedSimpleObject> managedSimpleObjects = new List<ManagedSimpleObject>();
            Int32 layerCount = (Int32)SimpleScene_GetLayerCount();

            for (Int32 i = 0; i < layerCount; ++i)
            {
                IntPtr layer = SimpleScene_GetLayerWithIdx(i);

                IntPtr entity = SimpleLayer_EntitiesBegin(layer);
                IntPtr end = SimpleLayer_EntitiesEnd(layer);

                while (entity != end)
                {
                    ManagedSimpleObject simpleObject = new ManagedSimpleObject();
                    simpleObject.SetSimpleObject(entity);
                    managedSimpleObjects.Add(simpleObject);

                    entity = SimpleLayer_EntitiesNext(layer);
                }
            }
            return managedSimpleObjects;
        }

        public void MoveCamera(float dx, float dy)
        {
            int wX = (int)dx; int wY = (int)dy;
            SimpleCamera2D_ScreenToWorld(ref wX, ref wY);
            int wOX = 0; int wOY = 0;
            SimpleCamera2D_ScreenToWorld(ref wOX, ref wOY);

            int deltaX = wX - wOX;
            int deltaY = wY - wOY;

            SimpleCamera2D_Move(deltaX, -deltaY);

        }


        public void DeltaZoom(float dz)
        {
            SimpleCamera2D_DeltaZoom(dz);
        }

        public float GetZoom()
        {
            return SimpleCamera2D_GetZoom();
        }

        public void SetZoom(float z)
        {
            SimpleCamera2D_SetZoom(z);
        }

        public void Restart()
        {
            SimpleEngine_Shutdown();
            Initialize();

        }

        //Custom events
        event EventHandler OnEngineInitialized;

        int MaxZoom
        {
            get
            {
                if (SimpleEngine_GetScene() != IntPtr.Zero)
                    return (int)SimpleCamera2D_GetMaxZoom();
                return 100;

            }
        }

        List<ManagedSimpleLayer> ManagedSimpleLayers
        {

            get
            {
                List<ManagedSimpleLayer> managedSimpleLayers = new List<ManagedSimpleLayer>();

                IntPtr scene = SimpleEngine_GetScene();
                if (scene != IntPtr.Zero)
                {

                    int layerCount = (int)SimpleScene_GetLayerCount();
                    for (int i = 0; i < layerCount; ++i)
                    {
                        IntPtr nativeLayer = SimpleScene_GetLayerWithIdx(i);
                        ManagedSimpleLayer layer = new ManagedSimpleLayer(nativeLayer);
                        managedSimpleLayers.Add(layer);
                    }

                }

                return managedSimpleLayers;
            }


        }


    }

}
