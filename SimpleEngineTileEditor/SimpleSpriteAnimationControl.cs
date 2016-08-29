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

    //    IntPtr _simpleSpriteAnimation;
    //    ManagedSimpleObject _managedSimpleObject;

    //    public ManagedSimpleObject GetManagedSimpleObject()
    //    {

    //        return _managedSimpleObject;

    //    }
    //    public SimpleSpriteAnimationControl()
    //    {
    //        _managedSimpleObject = new ManagedSimpleObject();
    //        _simpleSpriteAnimation = SimpleSpriteAnimation_Create();
    //    }

    //    ~SpriteSheetControl()
    //    {
    //        SimpleSpriteSheetRenderer_Destroy(_simpleSpriteSheetRenderer);
    //    }

    //    public int AddControl(String path, int x, int y, int w, int h)
    //    {

    //        //remove temp
    //        int from = path.IndexOf("/temp/");
    //        path = path.Remove(0, from + 6);

    //        //Try to find spritesheet to use
    //        IntPtr spriteSheet = SimpleRenderer_GetSpriteSheet(path);

    //        if (spriteSheet == IntPtr.Zero)
    //        {

    //            SimpleRenderer_CreateSpriteSheetEmpty(path);
    //            spriteSheet = SimpleRenderer_GetSpriteSheet(path);
    //        }

    //        int idx = SimpleSpriteSheet_GetFrameIndex(spriteSheet, x, y, w, h);
    //        if (idx == -1)
    //            idx = SimpleSpriteSheet_AddSpriteFrame(spriteSheet, x, y, w, h);

    //        //Configure brush
    //        TileEditorApp_SetCursorTile(path, idx);
    //        return idx;
    //    }

    //    public float positionX
    //    {
    //        get
    //        {
    //            if (_simpleSpriteSheetRenderer == IntPtr.Zero)
    //                return 0.0f;
    //            float x = 0.0f;
    //            float y = 0.0f;
    //            float z = 0.0f;
    //            SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
    //            float ix = x;
    //            float iy = y;
    //            SimpleCamera2D_WorldToScreen(ref ix, ref iy);
    //            return ix;
    //        }

    //        set
    //        {

    //            float x = 0.0f;
    //            float y = 0.0f;
    //            float z = 0.0f;
    //            SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);

    //            float ix = value;
    //            float iy = y;
    //            SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
    //            SimpleObject_SetX(_simpleSpriteSheetRenderer, ix);
    //        }
    //    }

    //    public float positionY
    //    {
    //        get
    //        {
    //            if (_simpleSpriteSheetRenderer == IntPtr.Zero)
    //                return 0.0f;
    //            float x = 0.0f;
    //            float y = 0.0f;
    //            float z = 0.0f;
    //            SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
    //            float ix = x;
    //            float iy = y;
    //            SimpleCamera2D_WorldToScreen(ref ix, ref iy);
    //            return iy;
    //        }

    //        set
    //        {

    //            float x = 0.0f;
    //            float y = 0.0f;
    //            float z = 0.0f;
    //            SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);

    //            float ix = value;
    //            float iy = y;
    //            SimpleCamera2D_ScreenToWorld(ref ix, ref iy);
    //            SimpleObject_SetY(_simpleSpriteSheetRenderer, iy);

    //        }
    //    }

    //    public float positionZ
    //    {
    //        get
    //        {
    //            float x = 0.0f;
    //            float y = 0.0f;
    //            float z = 0.0f;
    //            SimpleObject_GetPosition(_simpleSpriteSheetRenderer, ref x, ref y, ref z);
    //            return z;
    //        }

    //        set
    //        {
    //            SimpleObject_SetZ(_simpleSpriteSheetRenderer, value);
    //        }
    //    }

    //    public float width
    //    {
    //        get
    //        {
    //            float w = 0.0f;
    //            SimpleObject_GetWidth(_simpleSpriteSheetRenderer, ref w);
    //            return w;
    //        }

    //        set
    //        {
    //            SimpleObject_SetWidth(_simpleSpriteSheetRenderer, value);
    //        }
    //    }

    //    public float height
    //    {
    //        get
    //        {
    //            float h = 0.0f;
    //            SimpleObject_GetHeight(_simpleSpriteSheetRenderer, ref h);
    //            return h;
    //        }

    //        set
    //        {
    //            SimpleObject_SetHeight(_simpleSpriteSheetRenderer, value);
    //        }
    //    }
    //}
}
}
