using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class TileMapControl
    {
        #region SimpleEngineImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleEngine_GetGameLogic();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern String SimpleEngine_GetSceneState();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_SetSceneState(String state);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern String SimpleEngine_GetGameLogicState();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleEngine_SetGameLogicState(String state);
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
        static extern void TileEditorApp_NewMap();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_LoadState(String gameState);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern String TileEditorApp_GetState();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetMapSize(int width, int height);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetMapWidth(int width);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetMapHeight(int height);

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_SetCursorErase();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern void TileEditorApp_Paint();


        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern int TileEditorApp_GetMapWidth();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern int TileEditorApp_GetMapHeight();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern String TileEditorApp_Serialize();

        [DllImport("SimpleEngineNativeTileEditor.dll")]
        static extern bool TileEditorApp_Deserialize(String node);
        #endregion


        public TileMapControl() {
        
        }
        ~TileMapControl() {
            
        }
        void SetBrush(String path, Int32 idx) {
            TileEditorApp_SetCursorTile(path, idx);
        }
        void IdleBrush() {
            TileEditorApp_SetCursorIdle();
        }
        void EraseBrush() {
            TileEditorApp_SetCursorErase();

        }
        void Paint() {

            if (SimpleEngine_GetGameLogic() != IntPtr.Zero)
                TileEditorApp_Paint();

        }
        String TakeSnapshot() {
            return SimpleEngine_GetGameLogicState();

        }
        void RestoreSnapshot(String state) {
            SimpleEngine_SetGameLogicState(state);
        }

        //Properties

        int MapWidth
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

        int MapHeight
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
