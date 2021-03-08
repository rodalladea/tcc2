import fs from 'fs';
import path from 'path';
import { v4 } from 'uuid';
import upload from '../utils/storage/upload';
import AppError from '../errors/AppErrors';

interface XBIdataInterface {
    id: string;
    basePicture: string | null;
    targetPicture: string | null;
    imageDiff: number;
    chiSquared: number;
    phash: number;
    positionLeft: number;
    positionRight: number;
    positionY: number;
    visibilityLeft: number;
    visibilityRight: number;
    widthComparison: number;
    heightComparison: number;
}

async function uploadPictures(): Promise<Record<string, unknown>> {
    try {
        const data = fs
            .readFileSync(
                path.join(
                    __dirname,
                    '../../results/chrome_win-firefox_win.arff',
                ),
            )
            .toString('utf-8');

        const rows = data.split('@DATA')[1].trim().split('\n');

        const allData = await rows.reduce(async (promise, curr: string) => {
            return promise.then(async acc => {
                const itens = curr.split(',');

                const positionLeft = Math.abs(
                    (parseInt(itens[40], 10) - parseInt(itens[41], 10)) /
                        (parseInt(itens[31], 10) - parseInt(itens[32], 10)),
                );
                const positionRight = Math.abs(
                    (parseInt(itens[44], 10) - parseInt(itens[45], 10)) /
                        (parseInt(itens[31], 10) - parseInt(itens[32], 10)),
                );
                const positionY = Math.abs(
                    (parseInt(itens[41], 10) - parseInt(itens[42], 10)) /
                        (parseInt(itens[31], 10) - parseInt(itens[32], 10)),
                );

                const visibilityLeft =
                    Math.abs(
                        parseInt(itens[44], 10) - parseInt(itens[31], 10),
                    ) -
                    Math.abs(parseInt(itens[45], 10) - parseInt(itens[32], 10));
                const visibilityRight =
                    Math.abs(
                        parseInt(itens[40], 10) - parseInt(itens[31], 10),
                    ) -
                    Math.abs(parseInt(itens[41], 10) - parseInt(itens[32], 10));

                const widthComparison = Math.abs(
                    (parseInt(itens[21], 10) - parseInt(itens[22], 10)) /
                        (parseInt(itens[31], 10) - parseInt(itens[32], 10)),
                );

                let max = 1;
                if (parseInt(itens[19], 10) >= parseInt(itens[20], 10)) {
                    max = parseInt(itens[19], 10);
                } else {
                    max = parseInt(itens[20], 10);
                }

                const heightComparison = Math.abs(
                    (parseInt(itens[19], 10) - parseInt(itens[20], 10)) / max,
                );

                let basePicture = null;
                let targetPicture = null;
                if (itens[13] !== 'null') {
                    basePicture = await upload(
                        itens[13],
                        itens[13].split('\\')[2],
                    );
                }

                if (itens[14] !== 'null') {
                    targetPicture = await upload(
                        itens[14],
                        itens[14].split('\\')[2],
                    );
                }

                const XBIdata = {
                    id: v4(),
                    basePicture,
                    targetPicture,
                    imageDiff: parseFloat(itens[27]),
                    chiSquared: parseFloat(itens[28]),
                    phash: parseFloat(itens[38]),
                    positionLeft:
                        positionLeft === Infinity || Number.isNaN(positionLeft)
                            ? 0
                            : positionLeft,
                    positionRight:
                        positionRight === Infinity ||
                        Number.isNaN(positionRight)
                            ? 0
                            : positionRight,
                    positionY:
                        positionY === Infinity || Number.isNaN(positionY)
                            ? 0
                            : positionY,
                    visibilityLeft:
                        visibilityLeft === Infinity ||
                        Number.isNaN(visibilityLeft)
                            ? 0
                            : visibilityLeft,
                    visibilityRight:
                        visibilityRight === Infinity ||
                        Number.isNaN(visibilityRight)
                            ? 0
                            : visibilityRight,
                    widthComparison:
                        widthComparison === Infinity ||
                        Number.isNaN(widthComparison)
                            ? 0
                            : widthComparison,
                    heightComparison:
                        heightComparison === Infinity ||
                        Number.isNaN(heightComparison)
                            ? 0
                            : heightComparison,
                };

                acc.push(XBIdata);

                return acc;
            });
        }, Promise.resolve([] as Array<XBIdataInterface>));

        const arffFile = await upload(
            'results/chrome_win-firefox_win.arff',
            'chrome_win-firefox_win.arff',
        );

        return { arffFile, allData };
    } catch (err) {
        console.log(err);

        throw new AppError('Error read file');
    }
}

export default uploadPictures;
