using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    public class SpriteSheetControl
    {
        #region SimpleSpriteSheetRendererImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleSpriteSheetRenderer_Create();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleSpriteSheetRenderer_Destroy(IntPtr sprite);
        #endregion
        #region SimpleRendererImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleRenderer_GetSpriteSheet(String texturePath);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleRenderer_CreateSpriteSheet(String texturePath, int frameSizeX, int frameSizeY, int frameCountX, int frameCountY);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleRenderer_CreateSpriteSheetEmpty(String texturePath);
        #endregion
        #region SimpleSpriteSheet
        [DllImport("SimpleEngine_dyn.dll")]
        static extern int SimpleSpriteSheet_GetFrameIndex(IntPtr sheet, int positionX, int positionY, int sizeX, int sizeY);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern int SimpleSpriteSheet_AddSpriteFrame(IntPtr sheet, int positionX, int positionY, int sizeX, int sizeY);
        #endregion
        #region NativeTileEditorAppImports
        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorTile(String sheet, Int32 index);
        #endregion
        #region SimpleObjectImports
        //Managed simple object imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetPosition(IntPtr sObj, ref float x, ref float y, ref float z);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_Getx(IntPtr sObj, ref float x);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetY(IntPtr sObj, ref float y);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetZ(IntPtr sObj, ref float z);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetSize(IntPtr sObj, ref float width, ref float height);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetWidth(IntPtr sObj, ref float width);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetHeight(IntPtr sObj, ref float height);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_GetOrientation(IntPtr sObj, ref float orientation);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern UInt32 SimpleObject_GetName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern String SimpleObject_GetStringName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetPosition(IntPtr sObj, float x, float y, float z);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetX(IntPtr sObj, float x);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetY(IntPtr sObj, float y);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetZ(IntPtr sObj, float z);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetSize(IntPtr sObj, float width, float height);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetWidth(IntPtr sObj, float width);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetHeight(IntPtr sObj, float height);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetOrientation(IntPtr sObj, float orientation);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleObject_SetName(IntPtr sObj, String name);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern UInt32 SimpleObject_GetType(IntPtr sObj);

        //Camera imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_WorldToScreen(ref Int32 x, ref Int32 y);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleCamera2D_ScreenToWorld(ref Int32 x, ref Int32 y);

        #endregion
        IntPtr _simpleSpriteSheetRenderer;
        ManagedSimpleObject _managedSimpleObject;

        public ManagedSimpleObject GetManagedSimpleObject() {

            return _managedSimpleObject;

        }
        public SpriteSheetControl() {
            _managedSimpleObject = new ManagedSimpleObject();
            _simpleSpriteSheetRenderer = SimpleSpriteSheetRenderer_Create();
        }

        ~SpriteSheetControl() {
            SimpleSpriteSheetRenderer_Destroy(_simpleSpriteSheetRenderer);
        }

        public int AddControl(String path, int x, int y, int w, int h){

            //remove temp
            int from = path.IndexOf("/temp/");
            path.Remove(0, from + 6);

            //Try to find spritesheet to use
            IntPtr spriteSheet = SimpleRenderer_GetSpriteSheet(path);

            if (spriteSheet == IntPtr.Zero) {

                SimpleRenderer_CreateSpriteSheetEmpty(path);
                spriteSheet = SimpleRenderer_GetSpriteSheet(path);
            }

            int idx = SimpleSpriteSheet_GetFrameIndex(spriteSheet,x,y,w,h);
            if (idx == -1)
                idx = SimpleSpriteSheet_AddSpriteFrame(spriteSheet, x, y, w, h);

            //Configure brush
            TileEditorApp_SetCursorTile(path, idx);
             return idx;
        }

        public float positionX
        {
            get
            {
                if (_simpleSpriteSheetRenderer == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
                int ix = (int)x;
                int iy = (int)y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return ix;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);

                int ix = (int)value;
                int iy = (int)y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetX(_simpleSpriteSheetRenderer, ix);
            }
        }

        public float positionY
        {
            get
            {
                if (_simpleSpriteSheetRenderer == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
                int ix = (int)x;
                int iy = (int)y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return iy;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);

                int ix = (int)value;
                int iy = (int)y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetY(_simpleSpriteSheetRenderer, iy);

            }
        }

        public float positionZ
        {
            get
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
                return z;
            }

            set
            {
                SimpleObject_SetZ(_simpleSpriteSheetRenderer, value);
            }
        }

        public float width
        {
            get
            {
                float w = 0.0f;
                SimpleObject_GetWidth(_simpleSpriteSheetRenderer, ref w);
                return w;
            }

            set
            {
                SimpleObject_SetWidth(_simpleSpriteSheetRenderer, value);
            }
        }

        public float height
        {
            get
            {
                float h = 0.0f;
                SimpleObject_GetHeight(_simpleSpriteSheetRenderer, ref h);
                return h;
            }

            set
            {
                SimpleObject_SetHeight(_simpleSpriteSheetRenderer, value);
            }
        }
    }
}
