# Testing and Results

## Reported test plan

| Scenario | Setup | Expected / observed result |
|---|---|---|
| Empty bin | Sensor at about 3 m; rain off; network connected | LCD `Empty`; dashboard `0%` fill |
| Half-full bin | Sensor at about 1.5 m; rain off; network connected | LCD `Middle`; dashboard `50%` fill |
| Full bin | Sensor at < 0.3 m; rain off; network connected | LCD `Full`; dashboard `90%` fill |
| Rain condition | Rain triggered regardless of ultrasonic reading | LCD `Rain Detected`; fill update paused |

## Reported test outcome

The publication states that across the described scenarios, sensor inputs and outputs were correct in 99% of test repetitions.

## Performance table

| Metric | Value | Interpretation in the publication |
|---|---:|---|
| Fill-level accuracy | 99% | Correct readings across the reported tests |
| Rain detection accuracy | 99% | Correct rain-condition classification |
| Update latency | < 2 s average | Time for data to appear on dashboard after the reporting interval |
| Within-2-second cases | 95% | Share of cases reported within 2 s |
| Network reliability | 99% successful transmissions | Automatic reconnection reported after brief dropouts |

## Reproducibility checklist

- [ ] Recover original FYP firmware.
- [ ] Recover original wiring/pinout diagram.
- [ ] Record exact sensor models/variants.
- [ ] Confirm exact bin dimensions and calibration constants.
- [ ] Export original ThingSpeak screenshots.
- [ ] Add raw experimental measurements.
- [ ] Re-run empty/half/full/rain test cases.
- [ ] Compute accuracy from raw observations, not from summarized claims.

## Measurement-unit note

The accessible publication states that the prototype bin is 3 ft tall but its published empty-bin test row says the sensor measured 3 m. This repository keeps that statement as reported so that the original wording is not silently altered. The implementation should use measured/calibrated dimensions from the actual prototype.
