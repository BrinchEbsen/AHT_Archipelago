$tool_path = "../../mod_utility.exe"
$tool_exists = Test-Path -Path $tool_path
if (!$tool_exists) {
    Write-Host "Could not find mod utility."
    exit 1
}

$curr_dir = Get-Location

$code_us_output = "$curr_dir/.config/AR_Code_NTSC.txt"
$code_eu_output = "$curr_dir/.config/AR_Code_PAL.txt"

& $tool_path `
    export-cheat `
    AHT_Archipelago `
    action_replay `
    --build=GC_NTSC `
    --output=$code_us_output `
    --yes

if ($LastExitCode -ne 0) {
    Write-Host "Error outputting GC NTSC code."
    exit 1
} else {
    $content = Get-Content -Path $code_us_output | Select-Object -Skip 2
    Set-Content -Path $code_us_output -Value $content
}

& $tool_path `
    export-cheat `
    AHT_Archipelago `
    action_replay `
    --build=GC_PAL `
    --output=$code_eu_output `
    --yes

if ($LastExitCode -ne 0) {
    Write-Host "Error outputting GC PAL code."
    exit 1
} else {
    $content = Get-Content -Path $code_eu_output | Select-Object -Skip 2
    Set-Content -Path $code_eu_output -Value $content
}

exit 0
