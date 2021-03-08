import { v4 } from 'uuid';
import path from 'path';
import fs from 'fs';

async function upload(pathToFile: string, filename: string): Promise<string> {
    const fileFullname = `${v4()}${filename}`;

    fs.copyFileSync(
        path.join(__dirname, `../../../${pathToFile}`),
        path.join(__dirname, `../../upload/${fileFullname}`),
    );

    return `http://localhost:${process.env.PORT}/upload/${fileFullname}`;
}

export default upload;
