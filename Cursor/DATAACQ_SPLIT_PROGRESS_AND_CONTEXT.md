## dataAcq split — Progress and Context (Win32, C++20)

### What we built
- New standalone repo `dataAcq` (Win32 SDI MFC app, VS2022, C++20).
- SDI skeleton with standard doc-template (menu shows, main frame loads).
- Acquisition code copied from dbWave64:
  - `data_acquisition/` (DataTranslation AD/DA, dialogs, cyberamp, USBPxx*, dtacq32, dtplot32, ViewADcontinuous).
  - `chart/` minimal (ChartData/ChartDataAD/ChartWnd), `Controls/` minimal (Ruler/RulerBar/Scale), core datafile (`data_file/` Awave/X), WaveBuf, Taglist, AcqWave*.
  - Vendor headers: `include/DataTranslation/*` (libs copied: oldaapi32/oldsp32/OLMEM32/Graph32/olmemsup).
- Resources wired:
  - Copied `dbWave.rc` and `resource.h` as `dbWave_src.rc` and `resource_dbwave_src.h`; included in `dataAcq.rc`.
  - Fixed RC issues: removed `resource.hm`, resolved `HIDC_RADIO2`, guarded `IDR_MAINFRAME`.
- Mailbox helpers:
  - `Mailbox.h/.cpp`: session folder under Documents, append-only `manifest.txt` (mutex-protected), `diary.txt` (timestamped).

### Current app state
- Builds in Debug|Win32 (C++20). App starts with a visible frame and menu.
- View/Dialogs resources present; `ViewADcontinuous` and AD/DA dialogs compile.
- DataTranslation headers/libs present; runtime requires DT OpenLayers (32-bit) installed/registered.

### Next actions (Phase 1)
1) Wire mailbox calls into acquisition flow in `ViewADcontinuous`:
   - On session start: `AppendDiaryLine(session, L"session_start")`.
   - On file open: `AppendDiaryLine(session, L"start_file <abs>")`.
   - On finalize: `AppendDiaryLine(session, L"file_finalized <abs>")` + `AppendManifestLine(session, abs)`.
   - On stop: `AppendDiaryLine(session, L"stopped")`.
2) Verify UI end-to-end with DT card: board selection, start/stop, write `.dat` files.
3) Adjust any missing resource IDs incrementally (strip more Help IDs `HIDC_*` if they surface).

### Decisions captured
- Separate repo for `dataAcq` (decoupled evolution).
- Append-only `manifest.txt` (absolute paths, one finalized file per line).
- Human `diary.txt` with markers to slice per-file comments during dbWave64 import.
- C++20 enabled for dataAcq; dbWave64 remains at C++14 for now.

### Known caveats
- Resource ID collisions may still surface; resolve by pruning unused blocks or aliasing.
- Ensure DT OpenLayer ActiveX/runtime (32-bit) is installed.

### Paths of interest
- App: `dataAcq\dataAcq.sln`
- Mailbox: `dataAcq\dataAcq\Mailbox.*`
- Acquisition view: `dataAcq\dataAcq\data_acquisition\ViewADcontinuous.*`
- Included resources: `dataAcq\dataAcq\dataAcq.rc` includes `dbWave_src.rc` and `resource_dbwave_src.h`


