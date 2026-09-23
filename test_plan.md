# Test Plan Table

| Scenario | Inputs | Network | Reported result |
|---|---|---|---|
| Empty | ~3 m distance, rain off | Connected | `Empty`, 0% fill |
| Half-full | ~1.5 m distance, rain off | Connected | `Middle`, 50% fill |
| Full | <0.3 m distance, rain off | Connected | `Full`, 90% fill |
| Rain | Rain trigger | Any | `Rain Detected`, fill update paused |
