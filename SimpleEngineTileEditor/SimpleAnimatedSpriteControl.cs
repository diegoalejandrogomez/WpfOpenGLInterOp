using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class SimpleAnimatedSpriteControl
    {

        #region SimpleSpriteAnimationImports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleAnimatedSpriteRenderer_Create();
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_Destroy(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_SetAnimation(IntPtr sprite, IntPtr anim);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_SetAnimationWithName(IntPtr sprite, String anim);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_Play(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_PlayOnce(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_Stop(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleAnimatedSpriteRenderer_Pause(IntPtr sprite);
             
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
        #region SimpleRendererImports
        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleRenderer_GetSpriteAnimation(string name);
        #endregion
        #region NativeTileEditorAppImports
        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetCursorAnimated(String animationName);
        #endregion
        IntPtr _simpleSpriteAnimation;
        ManagedSimpleObject _managedSimpleObject;

        public ManagedSimpleObject GetManagedSimpleObject()
        {

            return _managedSimpleObject;

        }
        public SimpleAnimatedSpriteControl()
        {
            _managedSimpleObject = new ManagedSimpleObject();
            _simpleSpriteAnimation = SimpleAnimatedSpriteRenderer_Create();
        }

        ~SimpleAnimatedSpriteControl()
        {
            SimpleAnimatedSpriteRenderer_Destroy(_simpleSpriteAnimation);
        }

        public void AddControl(String animationName)
        {

            //Check if the animation exists... otherwise, we should assert
            IntPtr anim = SimpleRenderer_GetSpriteAnimation(animationName);

            if (anim == IntPtr.Zero)
                throw new Exception("Animation not found!");

            TileEditorApp_SetCursorAnimated(animationName);


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
