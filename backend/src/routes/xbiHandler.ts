import { Router, Request, Response } from 'express';

import AppError from '../errors/AppErrors';
import XBI from '../models/xbi.model';
import { AllDataXBIInterface } from '../models/xbi.types';

const router = Router();

router.post('/saveXBIs', async (req: Request, res: Response) => {
    try {
        const allData: AllDataXBIInterface = req.body.data;

        if (!allData.XBIs.length) return res.json({ success: false });

        const document = new XBI(allData);
        await document.save();

        return res.json({ success: true });
    } catch (err) {
        console.log(
            `An error occurred when tried to collect data from site ${err.message}`,
        );

        res.json({ success: false });

        throw new AppError('Error when tried to collect dat from site');
    }
});

export default router;
