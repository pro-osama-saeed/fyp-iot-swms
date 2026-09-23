# Source Status

## Attached FYP report

The file supplied in the conversation is:

`github-fyp-adp-iot-swms.pdf`

The uploaded byte stream is exactly 2 MiB and does not contain a valid PDF trailer/xref structure. Standard PDF tools therefore cannot open/render its pages. Because of this, the original report's figures, captions, tables, source-code appendices, wiring diagrams, and page-specific wording could not be faithfully extracted.

## What this repository currently uses

### Source-derived from the accessible 2026 publication

- Project title and publication metadata.
- System architecture and component roles.
- Hardware/software stack.
- Reporting interval.
- Rain-aware fill-reading behavior.
- LCD/ThingSpeak interaction.
- Testing scenarios.
- Reported performance metrics.
- Implementation notes and future-work directions.

### Project metadata

The academic context and ownership are recorded as an ADP Computer Networking final-year project based on the project context supplied with the task.

### Redrawn/reconstructed material

- `docs/figures/architecture.svg`
- `docs/figures/workflow.svg`
- `docs/figures/performance.svg`
- `src/esp32_smart_waste_monitoring_reference.ino`

These are repository-created representations, not recovered originals.

## What should be added after the complete report is available

1. Original FYP report PDF under `docs/original-report/`.
2. Original firmware/source files under `src/`.
3. Original wiring/circuit diagram under `hardware/`.
4. Prototype photographs under `docs/figures/photos/`.
5. ThingSpeak dashboard screenshots under `docs/figures/dashboard/`.
6. Raw experimental data under `data/raw/`.
7. Exact bill of materials and costs.
8. Original team/member/supervisor details from the report.

This separation keeps the repository accurate and makes later reconciliation straightforward.
