#!/data/data/com.termux/files/usr/bin/bash

echo "📦 Installing ytmedia CLI tool..."

# Go to project folder (assumes already cloned)
cd "$(dirname "$0")" || exit

# Build
mkdir -p bin
g++ src/yt_media.cpp -o bin/yt_media

# Make executable
chmod +x bin/yt_media

# Install globally in Termux
cp bin/yt_media $PREFIX/bin/ytmedia

echo "✅ Installed successfully!"
echo "👉 Now run: ytmedia"
