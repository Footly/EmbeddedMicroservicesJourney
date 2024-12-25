import fs from "fs";
import OpenAI from "openai";

// Get the PlantUML file path and output header file name from command-line arguments
const args = process.argv.slice(2);

const jsonPath = args[0];
const compID = args[1];
const plantumlBlueprint = args[2];
const mdBlueprint = args[3];

// Read the Json file content
let jsonPathContent;
try {
    jsonPathContent = fs.readFileSync(jsonPath, "utf-8");
} catch (error) {
    console.error(`Error reading file at ${jsonPath}:`, error.message);
    process.exit(1);
}

//Read  the PlantUML file content
let plantumlBlueprintContent;
try {
    plantumlBlueprintContent = fs.readFileSync(plantumlBlueprint, "utf-8");
}
catch (error) {
    console.error(`Error reading file at ${plantumlBlueprint}:`, error.message);
    process.exit(1);
}

// Read the Markdown file content
let mdBlueprintContent;
try {
    mdBlueprintContent = fs.readFileSync(mdBlueprint, "utf-8");
}
catch (error) {
    console.error(`Error reading file at ${mdBlueprint}:`, error.message);
    process.exit(1);
}

const openai = new OpenAI();

try {
    // Construct the new prompt
    const newPrompt = `For the component with id ${compID}, take the json object that has this id and generate a readme file using the following template: ${mdBlueprintContent} \n.
    and a plantuml diagram:${plantumlBlueprintContent} \n.
    Software relational datamodel connecting all items -> :\n${jsonPathContent}`;

    // Generate the completion from the OpenAI API
    const completion = await openai.chat.completions.create({
        model: "gpt-4o-mini",
        messages: [
            { role: "system", content: "You are a helpful assistant experienced in Sofwtare Development" },
            { role: "user", content: newPrompt } // Add the new prompt without appending to context history
        ],
    });

    // Extract the result
    const responseContent = completion.choices[0].message.content;
    console.log(responseContent);

    // Log the amount of tokens consumed
    const tokensConsumed = completion.usage.total_tokens;
    console.log(`Tokens consumed: ${tokensConsumed}`);
} catch (error) {
    console.error("Error generating header file:", error.message);
    process.exit(1);
}
