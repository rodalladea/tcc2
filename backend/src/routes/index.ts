import { Router } from 'express';

import collector from './collector';
import xbiHandler from './xbiHandler';

const routes = Router();

routes.use('/', collector);
routes.use('/', xbiHandler);

export default routes;
