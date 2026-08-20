// const canvas = document.getElementById("canvas");
// const ctx = canvas.getContext("2d", { alpha: false });
const canvasesDiv = document.getElementById("canvases");
const arraysBasePath = "collectables_generator/arrays/";

const json = {
    minimaps:       { path: "minimaps.json",                                        json: undefined },
    [19]:           { path: arraysBasePath+"00_19_Sunken_Ruins.json",               json: undefined },
    [20]:           { path: arraysBasePath+"01_20_Cloudy_Domain.json",              json: undefined },
    [21]:           { path: arraysBasePath+"02_21_Cloudy_Domain_Ball_Gadget.json",  json: undefined },
    [22]:           { path: arraysBasePath+"03_22_Dragonfly_Falls.json",            json: undefined },
    [23]:           { path: arraysBasePath+"04_23_Crocovile_Swamp.json",            json: undefined },
    [24]:           { path: arraysBasePath+"05_24_Dragon_Village.json",             json: undefined },
    [30]:           { path: arraysBasePath+"06_30_Dark_Mine.json",                  json: undefined },
    [31]:           { path: arraysBasePath+"07_31_Frostbite_Village.json",          json: undefined },
    [33]:           { path: arraysBasePath+"08_33_Ice_Citadel.json",                json: undefined },
    [35]:           { path: arraysBasePath+"09_35_Gloomy_Glacier.json",             json: undefined },
    [40]:           { path: arraysBasePath+"10_40_Reds_Laboratory.json",            json: undefined },
    [44]:           { path: arraysBasePath+"11_44_Stormy_Beach.json",               json: undefined },
    [45]:           { path: arraysBasePath+"12_45_Coastal_Remains.json",            json: undefined },
    [60]:           { path: arraysBasePath+"13_60_Molten_Mount.json",               json: undefined },
    [61]:           { path: arraysBasePath+"14_61_Magma_Falls_Top.json",            json: undefined },
    [62]:           { path: arraysBasePath+"15_62_Magma_Falls_Ball_Gadget.json",    json: undefined },
    [63]:           { path: arraysBasePath+"16_63_Magma_Falls_Bottom.json",         json: undefined },
    objectives:     { path: arraysBasePath+"17_Objectives.json",                    json: undefined },
    junk_chests:    { path: arraysBasePath+"18_Junk_Chests.json",                   json: undefined },
    dragon_elders:  { path: arraysBasePath+"19_Dragon_Elders.json",                 json: undefined },
    bosses:         { path: arraysBasePath+"20_Bosses.json",                        json: undefined },
    fireworks:      { path: arraysBasePath+"21_Fireworks.json",                     json: undefined }
};

const images = {};

// Reference: https://github.com/BrinchEbsen/AHT_SaveFileUtil/blob/master/AHT_SaveFileUtil/Save/MiniMap/MiniMapInfo.cs
function worldToPixel(mmJson, x, z)
{
    let worldXSpan = mmJson.world_edge[2] - mmJson.world_edge[0];
    let worldZSpan = mmJson.world_edge[1] - mmJson.world_edge[3];
    let pixelXSpan = mmJson.pixel_edge[2] - mmJson.pixel_edge[0];
    let pixelZSpan = mmJson.pixel_edge[3] - mmJson.pixel_edge[1];

    let xRatio = worldXSpan / pixelXSpan;
    let zRatio = worldZSpan / pixelZSpan;

    let zUp     = mmJson.world_edge[1] + (mmJson.pixel_edge[1] * zRatio);
    let xRight  = mmJson.world_edge[2] + (512 - mmJson.pixel_edge[2]) * xRatio;
    let zBottom = mmJson.world_edge[3] - (512 - mmJson.pixel_edge[3]) * zRatio;
    let xLeft   = mmJson.pixel_edge[0] - (mmJson.pixel_edge[0] * xRatio);

    let xSpan = Math.abs(xRight - xLeft);
    let zSpan = Math.abs(zUp - zBottom);

    let localX = Math.abs(x - xLeft);
    let localZ = Math.abs(z - zUp);

    let localXRatio = localX / xSpan;
    let localZRatio = localZ / zSpan;

    return [
        Math.floor(512 * localXRatio),
        Math.floor(512 * localZRatio)
    ];
}

function getMinimapJson(mapIndex)
{
    for (let i = 0; i < json.minimaps.json.length; i++)
    {
        if (json.minimaps.json[i].map_index == mapIndex)
        {
            return json.minimaps.json[i];
        }
    }

    return undefined;
}

function drawIconsOnMap(ctx, mapIndex)
{
    for (prop in json)
    {
        if (prop === "minimaps") continue;
        collJson = json[prop].json;

        for (let i = 0; i < collJson.length; i++)
        {
            if (collJson[i].map_index != mapIndex) continue;
    
            if ((collJson[i].x === undefined) || (collJson[i].z === undefined)) continue;
    
            if (collJson[i].type === "LightGem_MiniGame") continue;
    
            const xz = worldToPixel(getMinimapJson(mapIndex), collJson[i].x, collJson[i].z);
            console.log(mapIndex, xz);
            ctx.fillRect(xz[0]-4, xz[1]-4, 8, 8);
        }
    }
}

function main()
{
    console.log(json);
    console.log(images);

    for (prop in images)
    {
        const header = document.createElement("h1");
        header.textContent = ""+prop;
        canvasesDiv.appendChild(header);

        const canvas = document.createElement("canvas");
        canvas.height = 512;
        canvas.width = 512;
        canvas.id = "canvas_"+prop;
        canvasesDiv.appendChild(canvas);

        const ctx = canvas.getContext("2d", { alpha: false });
        ctx.drawImage(images[prop], 0, 0);
        drawIconsOnMap(ctx, prop);
    }
}

function preloadImage(mapIndex)
{
    return new Promise((resolve, reject) => {
        const img = new Image();
        img.src = "minimap_images/"+mapIndex+".png";
        img.onload = resolve;
        img.onerror = reject;
        images[mapIndex] = img;
    });
}

async function preloadJson()
{
    for (prop in json)
    {
        jsonFile = await fetch(json[prop].path);
        json[prop].json = await jsonFile.json();
    }
}

function init()
{
    preloadJson().then(() => {
        const promises = [];

        mmJson = json.minimaps.json;
        
        for (let i = 0; i < mmJson.length; i++)
        {
            const mm = mmJson[i];
            promises.push(preloadImage(mm.map_index));
        }

        Promise.all(promises).then(main);
    });
}

init();
