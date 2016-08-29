using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class SimpleSpriteAnimationControl
    {

        #region SimpleSpriteAnimationImports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleSpriteAnimation_Create();
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_Destroy(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_SetAnimationName(IntPtr sprite, String name);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_SetSpriteSheet(IntPtr sprite, IntPtr sheet);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_SetSpriteSheetWithName(IntPtr sprite, String sheetName);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SetFrames(IntPtr sprite, IntPtr frames, int amount);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_AddFrame(IntPtr sprite, int idx);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_ClearFrames(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleSpriteAnimation_SetFrameTime(IntPtr sprite, float frameTime);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern float SimpleSpriteAnimation_GetFrameTime(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int SimpleSpriteAnimation_GetFrameCount(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int SimpleSpriteAnimation_GetFrame(IntPtr sprite, int n);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleSpriteAnimation_GetSpriteSheet(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleSpriteAnimation_GetAnimationName(IntPtr sprite);
        #endregion
        #region SimpleObjectImports
        //Managed simple object imports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetPosition(IntPtr sObj, ref float x, ref float y, ref float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_Getx(IntPtr sObj, ref float x);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetY(IntPtr sObj, ref float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetZ(IntPtr sObj, ref float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetSize(IntPtr sObj, ref float width, ref float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetWidth(IntPtr sObj, ref float width);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetHeight(IntPtr sObj, ref float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_GetOrientation(IntPtr sObj, ref float orientation);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern UInt32 SimpleObject_GetName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleObject_GetStringName(IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetPosition(IntPtr sObj, float x, float y, float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetX(IntPtr sObj, float x);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetY(IntPtr sObj, float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetZ(IntPtr sObj, float z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetSize(IntPtr sObj, float width, float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetWidth(IntPtr sObj, float width);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetHeight(IntPtr sObj, float height);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetOrientation(IntPtr sObj, float orientation);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleObject_SetName(IntPtr sObj, String name);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern UInt32 SimpleObject_GetType(IntPtr sObj);
        #endregion
        #region SimpleCameraImports
        //Camera imports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleCamera2D_WorldToScreen(ref float x, ref float y);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleCamera2D_ScreenToWorld(ref float x, ref float y);

        #endregion

        IntPtr _simpleSpriteAnimation;
        ManagedSimpleObject _managedSimpleObject;

        public ManagedSimpleObject GetManagedSimpleObject()
        {

            return _managedSimpleObject;

        }
        public SimpleSpriteAnimationControl()
        {
            _managedSimpleObject = new ManagedSimpleObject();
            _simpleSpriteAnimation = SimpleSpriteAnimation_Create();
        }

        ~SimpleSpriteAnimationControl()
        {
            SimpleSpriteAnimation_Destroy(_simpleSpriteAnimation);
        }

        public int AddControl(String spriteSheet)
        {

            throw new NotImplementedException();
            ////remove temp
            //int from = path.IndexOf("/temp/");
            //path = path.Remove(0, from + 6);

            ////Try to find spritesheet to use
            //IntPtr spriteSheet = SimpleRenderer_GetSpriteSheet(path);

            //if (spriteSheet == IntPtr.Zero)
            //{

            //    SimpleRenderer_CreateSpriteSheetEmpty(path);
            //    spriteSheet = SimpleRenderer_GetSpriteSheet(path);
            //}

            //int idx = SimpleSpriteSheet_GetFrameIndex(spriteSheet, x, y, w, h);
            //if (idx == -1)
            //    idx = SimpleSpriteSheet_AddSpriteFrame(spriteSheet, x, y, w, h);

            ////Configure brush
            //TileEditorApp_SetCursorTile(path, idx);
            //return idx;
            return 0;
        }

        public float positionX
        {
            get
            {
                if (_simpleSpriteAnimation == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteAnimation, ref x, ref y, ref z);
                float ix = x;
                float iy = y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return ix;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteAnimation, ref x, ref y, ref z);

                float ix = value;
                float iy = y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetX(_simpleSpriteAnimation, ix);
            }
        }

        public float positionY
        {
            get
            {
                if (_simpleSpriteAnimation == IntPtr.Zero)
                    return 0.0f;
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteAnimation, ref x, ref y, ref z);
                float ix = x;
                float iy = y;
                SimpleCamera2D_WorldToScreen(ref ix, ref iy);
                return iy;
            }

            set
            {

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteAnimation, ref x, ref y, ref z);

                float ix = value;
                float iy = y;
                SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
                SimpleObject_SetY(_simpleSpriteAnimation, iy);

            }
        }

        public float positionZ
        {
            get
            {
                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;
                SimpleObject_GetPosition(_simpleSpriteAnimation, ref x, ref y, ref z);
                return z;
            }

            set
            {
                SimpleObject_SetZ(_simpleSpriteAnimation, value);
            }
        }

        public float width
        {
            get
            {
                float w = 0.0f;
                SimpleObject_GetWidth(_simpleSpriteAnimation, ref w);
                return w;
            }

            set
            {
                SimpleObject_SetWidth(_simpleSpriteAnimation, value);
            }
        }

        public float height
        {
            get
            {
                float h = 0.0f;
                SimpleObject_GetHeight(_simpleSpriteAnimation, ref h);
                return h;
            }

            set
            {
                SimpleObject_SetHeight(_simpleSpriteAnimation, value);
            }
        }

    }
}
