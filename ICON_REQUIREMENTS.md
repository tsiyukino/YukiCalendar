# Icon Requirements - Pending

**Status**: High Priority Complete, Medium/Low Priority Pending
**Last Updated**: 2026-02-15

---

## MEDIUM PRIORITY - Phase 5-6

### 1. Toolbar Icons (6 icons)
**Purpose**: Calendar page toolbar actions
**Format**: SVG, 20-24px
**Size**: 20x20 or 24x24 pixels

**Icons Needed**:
1. Add Event - Plus sign or calendar plus
2. Edit Event - Pencil or edit symbol
3. Delete Event - Trash can or X
4. Today - Target or calendar with dot
5. Previous - Left arrow
6. Next - Right arrow

**Location**: `resources/icons/toolbar/*.svg`

### 2. Module Node Icons (4 icons)
**Purpose**: Visual script editor nodes
**Format**: SVG, 16-20px

**Icons Needed**:
1. Start Action - Play button or flag
2. Reminder - Bell or notification
3. API Input - Cloud download or network
4. Variable - Box or constant symbol

**Location**: `resources/icons/modules/*.svg`

---

## LOW PRIORITY - Polish Phase

### 3. Event Type Icons (5 icons)
**Purpose**: Event category visualization
**Format**: SVG, 16px

**Icons Needed**:
1. Default - Calendar page
2. Meeting - People symbol
3. Task - Checkbox
4. Reminder - Bell
5. Appointment - Clock

**Location**: `resources/icons/event-types/*.svg`

### 4. Port Indicators (Optional)
**Purpose**: Visual script editor ports
**Format**: SVG, 12px

**Icons**: Input Port, Output Port, Execute Port

**Note**: May use colored circles instead

---

## Design Guidelines

- **Style**: Material Design, flat, professional
- **Colors**: Primary #6750a4, or theme-neutral
- **Format**: SVG preferred (scalable, ColorOverlay compatible)
- **Naming**: Lowercase, hyphen-separated (e.g., add-event.svg)

## Integration

Icons will be:
1. Added to `icons.qrc`
2. Referenced as `qrc:/icons/category/name.svg`
3. Colored dynamically via ColorOverlay
