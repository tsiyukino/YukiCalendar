#!/bin/bash
# Cleanup script to remove extra development documentation
# Keeps only: README.md, CHANGE.md, ICON_REQUIREMENTS.md

echo "Cleaning up extra documentation files..."

# Remove build-related docs
rm -f BUILD.md
rm -f BUILD_SUCCESS.md
rm -f RUNTIME_FIXES.md

# Remove status/implementation tracking docs
rm -f CURRENT_STATUS.md
rm -f IMPLEMENTATION_STATUS.md

# Remove session-specific docs
rm -f ICON_INTEGRATION.md
rm -f ICON_AND_SPACING_FIXES.md
rm -f UI_IMPROVEMENTS.md

echo "Cleanup complete!"
echo ""
echo "Remaining documentation:"
ls -1 *.md 2>/dev/null || echo "No markdown files found"
