using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    public class TileMapControl
    {
        #region SimpleEngineImports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern IntPtr SimpleEngine_GetGameLogic();
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleEngine_GetSceneState(StringBuilder state, int maxSize);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleEngine_SetSceneState(String state);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleEngine_GetGameLogicState(StringBuilder state, int maxSize);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleEngine_SetGameLogicState(String state);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleEngine_GetGameState(StringBuilder state, int maxSize);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleEngine_SetGameState(String state);

        #endregion
        #region NativeEditorImports
        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr TileEditorApp_Create();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_Destroy(IntPtr app);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetCursorPosition(float x, float y);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetCursorIdle();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetCursorTile(String sheet, Int32 index);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_NewMap();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_LoadState(String gameState);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern String TileEditorApp_GetState();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetMapSize(int width, int height);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetMapWidth(int width);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetMapHeight(int height);

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_SetCursorErase();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void TileEditorApp_Paint();


        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int TileEditorApp_GetMapWidth();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int TileEditorApp_GetMapHeight();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern String TileEditorApp_Serialize();

        [DllImport("SimpleEngineNativeTileEditor.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern bool TileEditorApp_Deserialize(String node);
        #endregion


        public TileMapControl() {
        
        }

        ~TileMapControl() {
            
        }

        public void SetBrush(String path, Int32 idx) {
            TileEditorApp_SetCursorTile(path, idx);
        }

        public void IdleBrush() {
            TileEditorApp_SetCursorIdle();
        }

        public void EraseBrush() {
            TileEditorApp_SetCursorErase();

        }

        public void Paint() {
            if (SimpleEngine_GetGameLogic() != IntPtr.Zero)
                TileEditorApp_Paint();
        }

        public String TakeSnapshot() {
            //TODO: Temporal fix, we should allocate dynamically this buffer
            StringBuilder builder = new StringBuilder(10240);
            SimpleEngine_GetGameState(builder, builder.Capacity);
            return builder.ToString();
        }

        public void RestoreSnapshot(String state) {
            SimpleEngine_SetGameState(state);
        }

        //Properties

        public int MapWidth
        {
            get
            {
                if (SimpleEngine_GetGameLogic() == IntPtr.Zero)
                    return 0;
                return TileEditorApp_GetMapWidth();

            }

            set
            {
                if (SimpleEngine_GetGameLogic() != IntPtr.Zero)
                    TileEditorApp_SetMapWidth(value);
            }
        }

        public int MapHeight
        {
            get
            {

                if (SimpleEngine_GetGameLogic() == IntPtr.Zero)
                    return 0;
                return TileEditorApp_GetMapHeight();
            }

            set
            {
                if (SimpleEngine_GetGameLogic() != IntPtr.Zero)
                    TileEditorApp_SetMapHeight(value);
            }
        }
    }
}
