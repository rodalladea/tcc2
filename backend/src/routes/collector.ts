import { Router, Request, Response } from 'express';
import fs from 'fs';
import path from 'path';

import AppError from '../errors/AppErrors';
import collect from '../utils/collect';
import merge from '../utils/merge';
import uploadPictures from '../services/uploadPictures';

const router = Router();

router.post('/collector', async (req: Request, res: Response) => {
    try {
        await collect(req.body.typedSite);
        await merge();

        const response = await uploadPictures();

        res.json(response);
    } catch (err) {
        console.log(
            `An error occurred when tried to collect data from site ${err.message}`,
        );

        res.json({ success: false });

        throw new AppError('Error when tried to collect dat from site');
    }
});

router.post('/setXBIs', async (req: Request, res: Response) => {
    try {
        res.json({ success: true });
    } catch (err) {
        console.log(`An error occurred when tried to set XBIs ${err.message}`);

        res.json({ success: false });

        throw new AppError('Error when tried set XBIs');
    }
});

router.get('/upload/:fileName', async (req: Request, res: Response) => {
    try {
        const fileBuffer = fs.readFileSync(
            path.join(__dirname, `../upload/${req.params.fileName}`),
        );

        if (
            req.params.fileName &&
            /png|jpeg|jpg/i.test(path.extname(req.params.fileName))
        ) {
            res.contentType('image/png');
            res.send(fileBuffer);
        } else {
            res.writeHead(200, {
                'Content-Disposition': `attachment; filename=${req.params.fileName}`,
                'Content-Length': fileBuffer.length,
            });
            res.end(fileBuffer);
        }
    } catch (err) {
        console.log(`An error occurred when tried to set XBIs ${err.message}`);

        res.json({ success: false });

        throw new AppError('Error when tried set XBIs');
    }
});

export default router;
