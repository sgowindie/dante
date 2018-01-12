#!/bin/bash

XOREncryptDecryptTool="$1/tools/$2"

echo "Encrypting Shaders..."

cd "$1/src/core/framework/graphics/opengl/shader"

$XOREncryptDecryptTool shader_001_frag.fsh shader_001_frag.ngs
echo "."
$XOREncryptDecryptTool shader_002_frag.fsh shader_002_frag.ngs
echo "."
$XOREncryptDecryptTool shader_003_frag.fsh shader_003_frag.ngs
echo "."
$XOREncryptDecryptTool shader_004_frag.fsh shader_004_frag.ngs
echo "."
$XOREncryptDecryptTool shader_001_vert.vsh shader_001_vert.ngs
echo "."
$XOREncryptDecryptTool shader_002_vert.vsh shader_002_vert.ngs
echo "."
$XOREncryptDecryptTool shader_003_vert.vsh shader_003_vert.ngs
echo "."

echo "Encrypting Textures..."

cd "$1/assets/textures"

$XOREncryptDecryptTool texture_000.png texture_000.ngt
echo "."
$XOREncryptDecryptTool texture_001.png texture_001.ngt
echo "."
$XOREncryptDecryptTool texture_002.png texture_002.ngt
echo "."
$XOREncryptDecryptTool texture_003.png texture_003.ngt
echo "."
$XOREncryptDecryptTool texture_004.png texture_004.ngt
echo "."
$XOREncryptDecryptTool texture_005.png texture_005.ngt
echo "."
$XOREncryptDecryptTool texture_006.png texture_006.ngt
echo "."
$XOREncryptDecryptTool texture_007.png texture_007.ngt
echo "."
$XOREncryptDecryptTool texture_008.png texture_008.ngt
echo "."

echo "Encrypting Normal Maps..."

$XOREncryptDecryptTool n_texture_001.png n_texture_001.ngt
echo "."
$XOREncryptDecryptTool n_texture_002.png n_texture_002.ngt
echo "."
$XOREncryptDecryptTool n_texture_003.png n_texture_003.ngt
echo "."
$XOREncryptDecryptTool n_texture_004.png n_texture_004.ngt
echo "."
$XOREncryptDecryptTool n_texture_005.png n_texture_005.ngt
echo "."
$XOREncryptDecryptTool n_texture_006.png n_texture_006.ngt
echo "."
$XOREncryptDecryptTool n_texture_007.png n_texture_007.ngt
echo "."
$XOREncryptDecryptTool n_texture_008.png n_texture_008.ngt
echo "."
